#curl -XGET 'http://localhost:9200/skyeye-2015.02.*,skyeye-2015.03.0*,skyeye-2015.03.10,skyeye-2015.03.11,skyeye-2015.03.12,skyeye-2015.03.13,skyeye-2015.03.14,skyeye-2015.03.15,skyeye-2015.03.16,skyeye-2015.03.17/_search?pretty' -d '
#curl -XGET 'http://localhost:9200/skyeye-2015.03.18,skyeye-2015.03.19,skyeye-2015.03.20,skyeye-2015.03.21,skyeye-2015.03.22,skyeye-2015.03.23,skyeye-2015.03.24,skyeye-2015.03.25/_search?pretty' -d '
#curl -XGET 'http://localhost:9200/skyeye-2015.02.*,skyeye-2015.03.*/_search?pretty' -d '
#curl -XPOST 'http://localhost:9200/_cache/clear?pretty'
#curl -XGET 'http://localhost:9200/skyeye-2015.02.*,skyeye-2015.03.*/_search?pretty' -d '
curl -XGET 'http://localhost:9200/skyeye-2015.03.26/_search?pretty' -d '
{
    "query": {
        "filtered": {
            "filter": {
                "bool": {
                    "must_not": [], 
                    "must": [
                        {
                            "range": {
                                  "@timestamp": {
                                      "lte": 1427299199000
                                  }
                            }
                        }
                    ]
                }
            }, 
            "query": {
                "query_string": {
                    "query": "sip:\"10.16.26.91\""
                }
            }
        }
    }, 
    "aggs": {
        "sip": {
            "terms": {
                "field": "sip", 
                "size": 500
            }, 
            "aggs": {
                "top_sip_hits": {
                    "top_hits": {
                        "sort": [
                            {"@timestamp": {"order": "asc"}}
                        ], 
                        "size": 1
                    }
                }
            }
        }
    }, 
    "size": 0
}'

