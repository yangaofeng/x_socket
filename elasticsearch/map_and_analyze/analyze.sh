curl -XGET 'localhost:9200/_analyze?pretty' -d '
{
      "analyzer" : "standard",
      "text" : "this is a test"
}'
