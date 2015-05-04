import org.elasticsearch.common.xcontent.XContentFactory.*;
import org.elasticsearch.common.xcontent.XContentBuilder;
import org.elasticsearch.common.xcontent.XContentFactory;
import org.elasticsearch.client.Client;
import org.elasticsearch.action.bulk.*;
import org.elasticsearch.common.transport.*;
import org.elasticsearch.common.settings.*;
import org.elasticsearch.client.transport.*;
import org.elasticsearch.common.inject.*;

import java.io.*;
import java.util.*;
import java.lang.reflect.Constructor;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DocValue {

    public final static int MAX_IP_COUNT = 100000;

    public static long ip2int(String ip) {
        String[] items = ip.split("\\.");
        return Long.valueOf(items[0]) << 24
                | Long.valueOf(items[1]) << 16
                | Long.valueOf(items[2]) << 8 | Long.valueOf(items[3]);
    }

    public static String int2ip(long ipInt) {
            StringBuilder sb = new StringBuilder();
            sb.append(ipInt & 0xFF).append(".");
            sb.append((ipInt >> 8) & 0xFF).append(".");
            sb.append((ipInt >> 16) & 0xFF).append(".");
            sb.append((ipInt >> 24) & 0xFF);
            return sb.toString();
    }

    static class Worker extends Thread {
        private String index;
        private Settings  settings;
        private String[] ip;
        private Random random = new Random(1000);

        Worker(String index, Settings settings, String[] ip) {
            this.index = index;
            this.settings = settings;
            this.ip = ip;
        }

        public void run() {
            try {
                Client client = new TransportClient(settings)
                        .addTransportAddress(new InetSocketTransportAddress("localhost", 9300));

                BulkRequestBuilder bulkRequest = null;


                Integer id = 0;
                double generate_used_ms = 0;
                double used_ms = 0;
                for (int i = 0; i < 100000; i++) { 

                    BulkRequestBuilder req = client.prepareBulk();

                    long start_ns = System.nanoTime();

                    for (int count = 0; count < 1000; count++) {
                        
                        id++;

                        XContentBuilder builder = XContentFactory.jsonBuilder();
                        req.add(client.prepareIndex(index, "ip_test", id.toString())
                                .setSource(builder
                                            .startObject()
                                                .field("ip", ip[Math.abs(random.nextInt() % ip.length)])
                                            .endObject()));

                    }

                    long end_ns = System.nanoTime();
                    generate_used_ms += ((double)(end_ns - start_ns)) / 1000 / 1000;

                    start_ns = System.nanoTime();
                    BulkResponse bulkResponse = req.execute().actionGet();
                    if (bulkResponse.hasFailures()) {
                        System.out.println("bulk api error: " + bulkResponse.buildFailureMessage());
                        return;
                    }
                    end_ns = System.nanoTime();
                    used_ms += ((double)(end_ns - start_ns)) / 1000 / 1000;

                    if (id % 10000 == 0) {
                        SimpleDateFormat dateformat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                        System.out.println(dateformat.format(new Date()) 
                                + ", current index: " + index + ", type: ip_test, current id: " + id 
                                + ", generate used time: " + String.format("%.3f", generate_used_ms)
                                + "ms, send used time: " + String.format("%.3f", used_ms) + "ms");
                        generate_used_ms = 0;
                        used_ms = 0;
                    }
                }

                client.close();

            } catch (Exception e) {
                e.printStackTrace();
            } 

        }
    }

    public static void main(String[] args) {

        Random random = new Random(1000);

        String[] index_array = {"ip_test_normal", "ip_test_doc_value", "ip_test_eager_loading"};

        System.out.println("start to generate ip");

        String[] ip = new String[MAX_IP_COUNT];
        for (int i = 0; i < MAX_IP_COUNT; i++) {
            ip[i] = int2ip(random.nextLong());
        }

        Settings settings = ImmutableSettings
                            .settingsBuilder()
                            .put("cluster.name", "es")
                            .put("client.transport.sniff", true)
                            .build();

        //for (int i = 0 ; i < 100; i++) {
        //    int t = Math.abs(random.nextInt() % 10000);
        //    System.out.println(ip[t]);
        //}

        Worker[] workers = new Worker[index_array.length];
        for (int i = 0; i < index_array.length; i++) {
            workers[i] = new Worker(index_array[i], settings, ip);
            workers[i].start();
        }

        for (int i = 0; i < workers.length; i++) {
            try {
                workers[i].join();
            } catch (InterruptedException e) {
            } 
        }
    }
}
