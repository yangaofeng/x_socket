#!/usr/bin/env bash

echo ""
echo "clear index---------------------------"
curl -XDELETE 'http://localhost:9200/ip_test_normal'
curl -XDELETE 'http://localhost:9200/ip_test_doc_value'
curl -XDELETE 'http://localhost:9200/ip_test_eager_loading'

curl -XPUT 'http://localhost:9200/ip_test_normal' -d '
{
    "mappings" : {
        "ip_test" : {
            "properties" : {
                "ip" : {
                    "type" : "ip",
                    "index" : "not_analyzed"
                }
            }
        }
    }
}'

curl -XPUT 'http://localhost:9200/ip_test_doc_value' -d '
{
    "mappings" : {
        "ip_test" : {
            "properties" : {
                "ip" : {
                    "type" : "ip",
                    "index" : "not_analyzed",
                    "doc_values" : true
                }
            }
        }
    }
}'

curl -XPUT 'http://localhost:9200/ip_test_eager_loading' -d '
{
    "mappings" : {
        "ip_test" : {
            "properties" : {
                "ip" : {
                    "type" : "ip",
                    "index" : "not_analyzed",
                    "fielddata": {
                        "loading": "eager"
                    }
                }
            }
        }
    }
}'

echo "allocate shareds................"

sh /root/es/bin/index.sh -i ip_test_normal allocate
sh /root/es/bin/index.sh -i ip_test_doc_value allocate
sh /root/es/bin/index.sh -i ip_test_eager_loading allocate

echo "complete"

