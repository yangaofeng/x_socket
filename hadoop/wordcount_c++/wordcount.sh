#!/usr/bin/env bash

hadoop jar ~/hadoop/hadoop-0.20.2/contrib/streaming/hadoop-0.20.2-streaming.jar \
        -file map/map \
        -file reduce/reduce \
        -input /home/yangaofeng/wordcount/data/* \
        -output /home/yangaofeng/wordcount/result \
        -mapper map/map \
        -reducer reduce/reduce

