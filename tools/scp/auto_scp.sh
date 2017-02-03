#/usr/bin/env bash

if [[ $# -ne 3 ]]; then
    echo "Usage: $0 <local_file> <host_list_file> <dest_dir>"
    exit
fi

local_dir=$(dirname $1)
local_file=$(basename $1)
host_list_file=$2
dest_dir=$3

user=$(whoami)
echo -n "$user password:"
read -s passwd

run_path=$(cd $(dirname $0); pwd)

for host in `cat $host_list_file`; do
    $run_path/scp.sh $local_dir $local_file $host $dest_dir $user $passwd
done

