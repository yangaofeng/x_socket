echo "ip test normal count:"
curl http://localhost:9200/ip_test_normal/_count?pretty

echo ""
echo "ip test doc value count:"
curl http://localhost:9200/ip_test_doc_value/_count?pretty

echo ""
echo "ip test eager loading count:"
curl http://localhost:9200/ip_test_eager_loading/_count?pretty
