nohup java -Xms4000m -Xmx4000m -XX:+UseParNewGC -XX:+UseConcMarkSweepGC -cp '.:/root/es/root/lib/elasticsearch-1.4.4.jar:/root/es/root/lib/lucene-core-4.10.3.jar' DocValue > send.log 2>&1 &

