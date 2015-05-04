#!/usr/bin/env bash

echo ""
echo "clear index---------------------------"
curl -XDELETE 'http://localhost:9200/ip_test_normal'
curl -XDELETE 'http://localhost:9200/ip_test_doc_value'
curl -XDELETE 'http://localhost:9200/ip_test_eager_loading'

echo "complete"

