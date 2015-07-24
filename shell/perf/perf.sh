#!/usr/bin/env bash

prefix="./"

help()
{
cat << HELP
Usage: $0 [-p] 
-----------------------------------
parameter statement: 
-p: path prefix of perf data
HELP
}

while [ -n "$1" ]; do 
    case "$1" in
        -h) help;exit;;
        -p) prefix=$2;shift 2;; 
        -*) echo "error: no such option $1. -h for help"; exit 1;; 
        *)break;
    esac
done

#echo "prefix:" $prefix

ps -eo tid,comm,args -L | grep database | grep -v grep | grep -v qlogd | grep -v vim  | sed 's/\/home.*//g' > t.txt

declare -A arr

while read x y
do
y=`echo $y | sed 's/ //g' | sed 's/:/-/g' | sed 's/\./-/g'`
#echo $x -- $y
if [ -z ${arr[$y]}  ]; then
	arr[$y]=$x
else
	arr[$y]=${arr[$y]}","$x
fi

done < t.txt

for t in ${!arr[@]};
do
	#echo $t ${arr[$t]}
	perf record -t ${arr[$t]} -o $prefix/${t}.data &
done

