curl http://localhost:9200/skyeye-dns-2015.03.19/_search?pretty -d'
{
    "query" : {
        "bool" : {
            "must": [
                { "match" : { "sip" : "10.16.0.222" } },
                { "match" : { "dip" : "10.16.13.14" } }
            ]
        }
    }
}'
