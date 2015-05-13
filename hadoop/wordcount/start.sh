#!/usr/bin/env bash
cat word.txt | php map.php | sort | php reduce.php | sort -k2 -n -r
