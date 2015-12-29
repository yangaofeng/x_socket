<?php

$pid = 0;
$quit = false;

function signal_handler($sig)
{
    global $pid;
    global $quit;
    if ($sig == SIGINT) {
        die("signal SIGINT received\n");
    } else if ($sig == SIGTERM) {
        die("signal SIGTERM received\n");
    } else if ($sig == SIGCHLD) {
        echo "signal SIGCHILD receiverd, child pid: $pid\n";
        pcntl_waitpid($pid, $status);
        echo "exit status: $status\n";
        $quit = true;
    } else {
        die("unknown signal: $sig\n");
    }
}

function child_signal_handler($sig)
{
    if ($sig == SIGINT) {
        exit("signal SIGINT received\n");
    } else if ($sig == SIGTERM) {
        exit("signal SIGTERM received\n");
    } 
}


function start_child()
{
    echo "start_child called\n";
    global $pid;
    $pid  = pcntl_fork();
    if ($pid == -1) {
        die("create child process filed\n");
    } else if ($pid == 0) {

        pcntl_signal(SIGINT, 'child_signal_handler');
        pcntl_signal(SIGTERM, 'child_signal_handler');

        $pid = getmypid();
        while (true) {
            //child process
            sleep(1); //worker function
            pcntl_signal_dispatch();
            echo "child process weak up\n";
        }

        exit("child process exit, $pid\n");
    } 

    return $pid;
}

pcntl_signal(SIGINT, 'signal_handler');
pcntl_signal(SIGTERM, 'signal_handler');
pcntl_signal(SIGCHLD, 'signal_handler');

while (true) {
    $pid = start_child();
    $quit = false;
    while (!$quit) {
        pcntl_signal_dispatch();
        sleep(1);
        //echo "quit: $quit\n";
    }

    echo "worker process $pid exit, and restart\n";
}

?>

