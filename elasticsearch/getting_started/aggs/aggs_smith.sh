curl -XGET 'http://localhost:9200/megacorp/employee/_search?pretty' -d '
{
    "query": {
        "match": {
            "last_name": "smith"
        }
    },
    "aggs": {
        "all_interests": {
            "terms": { "field": "interests" }
        }
    }
}
'
