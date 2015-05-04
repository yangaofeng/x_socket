echo "ip test normal aggs: ------------------------------------------------"
curl -XPOST 'http://localhost:9200/ip_test_normal/_cache/clear?pretty'
curl -XGET 'http://localhost:9200/ip_test_normal/_search?search_type=count&pretty' -d '
{
    "aggs" : {
        "ip_aggs" : {
            "terms" :  {
                "field" : "ip",
                "size" : 10,
                "shard_size" : 0
            }
        }
    }
}
'

echo "ip test doc value aggs: ------------------------------------------------"
curl -XPOST 'http://localhost:9200/ip_test_doc_value/_cache/clear?pretty'
curl -XGET 'http://localhost:9200/ip_test_doc_value/_search?search_type=count&pretty' -d '
{
    "aggs" : {
        "ip_aggs" : {
            "terms" :  {
                "field" : "ip",
                "size" : 10,
                "shard_size" : 0
            }
        }
    }
}
'

echo "ip test eager loading aggs, without clear cache: ------------------------------------------------"
#curl -XPOST 'http://localhost:9200/ip_test_eager_loading/_cache/clear?pretty'
curl -XGET 'http://localhost:9200/ip_test_eager_loading/_search?search_type=count&pretty' -d '
{
    "aggs" : {
        "ip_aggs" : {
            "terms" :  {
                "field" : "ip",
                "size" : 10,
                "shard_size" : 0
            }
        }
    }
}
'
