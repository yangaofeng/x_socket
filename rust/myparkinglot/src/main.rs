use std::sync::Arc;
use std::thread;
use std::time::Duration;

use parking_lot::Mutex;

fn main() {

    // #[cfg(feature = "deadlock_detection")]
    { // only for #[cfg]
        use parking_lot::deadlock;

        // Create a background thread which checks for deadlocks every 10s
        thread::spawn(move || {
            loop {
                thread::sleep(Duration::from_secs(10));
                let deadlocks = deadlock::check_deadlock();
                if deadlocks.is_empty() {
                    continue;
                }

                println!("{} deadlocks detected", deadlocks.len());
                for (i, threads) in deadlocks.iter().enumerate() {
                    println!("Deadlock #{}", i);
                    for t in threads {
                        println!("Thread Id {:#?}", t.thread_id());
                        println!("{:#?}", t.backtrace());
                    }
                }
            }
        });
    }

    let v1 = Arc::new(Mutex::new(0));
    let v2 = Arc::new(Mutex::new(0));

    let v11 = Arc::clone(&v1);
    let v21 = Arc::clone(&v2);
    let t1 = thread::spawn(move ||
        {
            println!("t1 attempting to lock v1");
            let _v1_guard = (*v11).lock();
            println!("t1 acquired v1");

            println!("t1 waiting ...");
            thread::sleep(Duration::from_secs(5));

            println!("t1 attempting to lock v2");
            let _v2_guard = (*v21).lock();

            println!("t1 acquired both locks");
        }
    );

    let v12 = Arc::clone(&v1);
    let v22 = Arc::clone(&v2);
    let t2 = thread::spawn(move ||
        {
            println!("t2 attempting to lock v2");
            let _v1_guard = (*v22).lock();
            println!("t2 acquired v2");

            println!("t2 waiting ...");
            thread::sleep(Duration::from_secs(5));

            println!("t2 attempting to lock v1");
            let _v2_guard = (*v12).lock();

            println!("t2 acquired both locks");
        }
    );

    t1.join().unwrap();
    t2.join().unwrap();
}
