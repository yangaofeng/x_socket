#!/usr/bin/env expect

if {$argc != 1} {
    send_user "Usage: mycp.sh host\n"
    exit
}

set timeout -1

set host [lindex $argv 0]
set user "username"
set passwd "password"
set remote_path "$user@$host:/home/s/apps/logtohadoop/php/configs/*.php"
set local_path $host
set cmd "/usr/bin/scp" 
#set para "-oUserKnownHostsFile=/dev/null -oStrictHostKeyChecking=no"

#send_user "cp command: $cmd\n"
#send_user "cp from $remote_path\n"
#send_user "cp to $local_path\n"

spawn $cmd $remote_path $local_path
expect {
    "yes/no)?" {
        send "yes\r"
        exp_continue
    }
    "password:" {
        send "$passwd\r"
        exp_continue
    }
    "Password:" {
        send "$passwd\r"
        exp_continue
    }
    eof {
        send_user "scp $host success\n"
    }
}

