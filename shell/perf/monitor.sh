#!/usr/bin/env bash

prefix="."

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

i=0

while true; do
    echo $prefix/$i
    mkdir -p $prefix/$i
    ./perf.sh -p $prefix/$i
    sleep 600
    killall perf
    i=$(($i+1))
done

