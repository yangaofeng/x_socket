echo "normal fielddata---------------------------------------------------------------"
curl -XGET 'http://localhost:9200/ip_test_normal/_stats/fielddata?fields=*&pretty' 

echo "doc value fielddata---------------------------------------------------------------"
curl -XGET 'http://localhost:9200/ip_test_doc_value/_stats/fielddata?fields=*&pretty' 

echo "eager loading fielddata---------------------------------------------------------------"
curl -XGET 'http://localhost:9200/ip_test_eager_loading/_stats/fielddata?fields=*&pretty' 
