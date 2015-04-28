#!/usr/bin/env bash

#wait second
wait_second=300
query_flag=true
facet_flag=true
debug_flag=false

help()
{
cat << HELP                                                                                                                                                                                                                                 
Usage: $0 [-w] [-q] [-f] [-d]
-----------------------------------
parameter statement: 
-w: wait second per query or facet
-q: query only
-f: facet only
-d: d, with one term for test
HELP
}

while [ -n "$1" ]; do 
    case "$1" in
        -h) help;exit;;
        -w) wait_second=$2;shift 2;; 
        -q) facet_flag=false;shift 1;; 
        -f) query_flag=false;shift 1;; 
        -d) debug_flag=true;shift 1;;
        -*) echo "error: no such option $1. -h for help"; exit 1;; 
        *)break;
    esac
done

echo "wait_second:" $wait_second
echo "query_flag:" $query_flag
echo "facet_flag:" $facet_flag
echo "debug_flag:" $debug_flag

multi_key="apple qq google baidu taobao jd sohu sina dianping nuomi"
single_key="360 360 360 360 360 360 360 360 360 360"

if [ "$debug_flag" == true ] ; then
    multi_key="apple"
    single_key="360"
fi

echo "multi key: " $multi_key
echo "single key: " $single_key

startdate=`date -d "1 day ago" "+%Y.%m.%d"`
enddate=`date "+%Y.%m.%d"`

starttime=$((`date -d "1 day ago" +%s%N` / 1000000))
endtime=$((`date +%s%N` / 1000000))

echo "start date:" $startdate
echo "end date:" $enddate
echo "start time:" $starttime
echo "end time:" $endtime


clear_cache()
{
    if [ "$debug_flag" == true ] ; then
        echo "return from clear_cache function"
        return 0
    fi

    echo "start clear cache"

    curl -XPOST 'http://localhost:9200/_cache/clear'
}

function query()
{
    #$1 key
    #$2 key number
    #$3 flag

    if [ "$query_flag" == false ]; then
        echo "return from query function"
        return 0
    fi

    echo "start a query, para: $1 $2 $3"

    curl -o query_${1}_${2}_${3}.txt -XGET \
    'http://10.16.66.191:9200/logstash-'$enddate',logstash-'$startdate'/_search?pretty' -d '
    {
      "query": {
        "query_string": {
          "query": "'$1'"
        }
      }
    }'
}

function facet()
{
    if [ "$facet_flag" == false ] ; then
        echo "return from facet function"
        return 0
    fi

    echo "start a facet, para: $1 $2 $3"

    #$1 key
    #$2 key number
    #$3 flag

    curl -o facet_${1}_${2}_${3}.txt -XGET \
    'http://10.16.66.191:9200/logstash-'$enddate',logstash-'$startdate'/_search?pretty' -d '{
      "facets": {
        "0": {
          "date_histogram": {
            "field": "@timestamp",
            "interval": "10m"
          },
          "global": true,
          "facet_filter": {
            "fquery": {
              "query": {
                "filtered": {
                  "query": {
                    "query_string": {
                      "query": "'$1'"
                    }
                  },
                  "filter": {
                    "bool": {
                      "must": [
                        {
                          "range": {
                            "@timestamp": {
                              "from": '$starttime',
                              "to": '$endtime'
                            }
                          }
                        }
                      ]
                    }
                  }
                }
              }
            }
          }
        }
      },
      "size": 0
    }'
}


#query

i=1
for k in $single_key; do
    sleep $wait_second
    query $k $i "single_key"
    sleep $wait_second
    facet $k $i "single_key"
    let i=i+1
done

i=1
for k in $multi_key; do
    sleep $wait_second
    query $k $i "multi_key"
    sleep $wait_second
    facet $k $i "multi_key"
    let i=i+1
done

#query with clear cache
i=1
for k in $single_key; do
    clear_cache
    sleep $wait_second
    query $k $i "single_key_no_cache"
    clear_cache
    sleep $wait_second
    facet $k $i "single_key_no_cache"
    let i=i+1
done

i=1
for k in $multi_key; do
    clear_cache
    sleep $wait_second
    query $k $i "multi_key_no_cache"
    clear_cache
    sleep $wait_second
    facet $k $i "multi_key_no_cache"
    let i=i+1
done

