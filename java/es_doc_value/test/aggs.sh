index='skyeye-'$1'-2015.03.30'
curl -XPOST 'http://localhost:9200/'$index'/_cache/clear?pretty'
#curl -XGET 'http://localhost:9200/'$index'/_search?search_type=count&pretty' -d '
#{
#    "aggs" : {
#        "sip_aggs" : {
#            "terms" :  {
#                "field" : "sip",
#                "size" : 10,
#                "shard_size" : 0
#            }
#        }
#    }
#}
#'
#
curl -XGET 'http://localhost:9200/'$index'/_search?search_type=count&pretty' -d '
{
    "query": {
        "filtered": {
            "query": {
                "query_string": {
                    "query": "baidu"
                }
            }
        }
    }, 
    "aggs" : {
        "sip_aggs" : {
            "terms" :  {
                "field" : "sip",
                "size" : 10,
                "shard_size" : 0
            }
        }
    }
}
'
