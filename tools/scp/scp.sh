#!/usr/bin/env expect

if {$argc != 6} {
    puts stderr "Usage: scp.sh <local_dir> <local_file> <host> <dest_dir> <user> <passwd>\n"
    exit
}

set timeout -1

set local_dir [lindex $argv 0]
set local_file [lindex $argv 1]
set host [lindex $argv 2]
puts "host: $host"
set dest_dir [lindex $argv 3]
set user [lindex $argv 4]
set passwd [lindex $argv 5]
set remote_path "$user@$host:/tmp"
set cmd "/usr/bin/scp" 

#set para "-oUserKnownHostsFile=/dev/null -oStrictHostKeyChecking=no"

#send_user "cp command: $cmd\n"
#send_user "cp from $remote_path\n"
#send_user "cp to $local_file\n"

proc do_expect {do_user do_pass} {
    expect {
        "yes/no)?" {
            send "yes\r"
            exp_continue
        }
        "password:" {
            send "$do_pass\r"
            exp_continue
        }
        "Password:" {
            send "$do_pass\r"
            exp_continue
        }
        "$do_user:" {
            send "$do_pass\r"
            exp_continue
        }
        eof {
            send_user "scp success\n"
        }
    }
}


spawn $cmd "$local_dir/$local_file" "$remote_path"
do_expect $user $passwd

spawn /usr/bin/ssh -t $host "sudo -u cloud cp /tmp/$local_file $dest_dir; rm -f /tmp/$local_file"
do_expect $user $passwd

