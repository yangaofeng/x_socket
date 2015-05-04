#include <stdlib.h>
#include <iostream>
#include <gflags/gflags.h>
#include "aggs.h"

using namespace std;
using namespace google;

DEFINE_string(host, "localhost", "request host");
DEFINE_int32(port, 9200, "request host port");
DEFINE_string(index, "", "request index");
DEFINE_string(type, "", "request type");
DEFINE_string(query, "*", "request query");
DEFINE_bool(aggs, true, "with aggregation");
DEFINE_int32(size, 0, "get record count");
DEFINE_int32(concurrency, 1, "concurrency query");


int main(int argc, char **argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);

    cout << "host: " << FLAGS_host << endl;
    cout << "port: " << FLAGS_port << endl;
    cout << "index: " << FLAGS_index << endl;
    cout << "type: " << FLAGS_type << endl;
    cout << "query: " << FLAGS_query << endl;
    cout << "aggs: " << FLAGS_aggs << endl;
    cout << "concurrency: " << FLAGS_concurrency << endl;

    Aggs aggs;

    if (!aggs.Init()) {
        cout << "aggs init failed" << endl;
        return -1;
    }

    aggs.Run();

    return 0;
}

