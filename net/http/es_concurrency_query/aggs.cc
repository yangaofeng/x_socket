#include <assert.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <gflags/gflags.h>
#include <stdio.h>
#include "aggs.h"

using namespace google;

DECLARE_string(host);
DECLARE_int32(port);
DECLARE_string(index);
DECLARE_string(type);
DECLARE_string(query);
DECLARE_bool(aggs);
DECLARE_int32(size);
DECLARE_int32(concurrency);

using namespace std;

bool Aggs::Init()
{
    assert(FLAGS_concurrency <= 1000);

    std::ostringstream o;

    o << "http://"
      << FLAGS_host
      << ":"
      << FLAGS_port;

    if (!FLAGS_index.empty()) {
        o << "/"
          << FLAGS_index;
    } else {
        time_t s = time(NULL);
        struct tm now;
        localtime_r(&s, &now);
        char buf[32];
        int n = sprintf(buf, "%04d.%02d.%02d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);
        o << "/"
          << "skyeye-"
          << buf;
    }

    if (!FLAGS_type.empty()) {
      o << "/" 
      << FLAGS_type;
    }
    
    o << "/_search?pretty";

    url_ = o.str();
    cout << "request url: " << url_ << endl;

    o.str("");

    o << "{"
    <<     "\"size\" : " << FLAGS_size << ","
    <<     "\"query\": {"
    <<         "\"filtered\": {"
    <<             "\"query\": {"
    <<                 "\"query_string\": {"
    <<                     "\"query\": \"" << FLAGS_query << "\""
    <<                 "}"
    <<             "}"
    <<         "}"
    <<     "}";

    if (FLAGS_aggs) {
        o << ","
        <<     "\"aggs\": {"
        <<         "\"agg_time\": {"
        <<             "\"date_histogram\": {"
        <<                 "\"field\": \"@timestamp\","
        <<                 "\"interval\": \"300000ms\","
        <<                 "\"min_doc_count\": 0"
        <<             "}"
        <<         "}"
        <<     "}";
    }

    o <<   "}";

    query_ = o.str();

    cout << "query: " << query_ << endl;

    curl_global_init(CURL_GLOBAL_ALL);
    multi_handle_ = curl_multi_init();
    assert(multi_handle_  != NULL);

    for (int i = 0; i < FLAGS_concurrency; i++) {
        CURL *easy_handle = curl_easy_init();
        std::ostringstream o;
        o << "es.";
        o << i;
        o << ".json";
        FILE *fp = fopen(o.str().c_str(), "ab+");

        curl_easy_setopt(easy_handle, CURLOPT_URL, url_.c_str());
        curl_easy_setopt(easy_handle, CURLOPT_POST, 1L);
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE,(long)query_.size());
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, query_.c_str());
        curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &save);
        curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

        curl_multi_add_handle(multi_handle_, easy_handle);

        easy_handles_.push_back(easy_handle);
        fps_.push_back(fp);
    }

    return true;
}

void Aggs::Run()
{
    int running_handle_count;
    while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(multi_handle_, &running_handle_count)) {
        cout << "running task count: " << running_handle_count << endl;
    }

    while (running_handle_count) {
        timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int max_fd;
        fd_set fd_read;
        fd_set fd_write;
        fd_set fd_except;

        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        FD_ZERO(&fd_except);

        curl_multi_fdset(multi_handle_, &fd_read, &fd_write, &fd_except, &max_fd);
        int return_code = select(max_fd + 1, &fd_read, &fd_write, &fd_except, &tv);
        if (-1 == return_code) {
            cerr << "select error." << endl;
            break;
        } else {
            while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(multi_handle_, &running_handle_count)) {
                cout << "running task count: " << running_handle_count << endl;
            }
        }
    }

    UsedTime();
}

void Aggs::UsedTime()
{
    double total_time = 0;
    for (int i = 0; i < FLAGS_concurrency; i++) {
        CURL *handle = easy_handles_[i];
        double used_time = 0;
        CURLcode rc = curl_easy_getinfo(handle, CURLINFO_TOTAL_TIME, &used_time);
        if (rc == CURLE_OK) {
            cout << "aggs " << i << " used time: " << used_time << endl;
            total_time += used_time;
        } else {
            cout << "aggs " << i << " get used time failed" << endl;
        }
    }

    cout << "total time: " << total_time << endl;
    cout << "average time: " << total_time / FLAGS_concurrency << endl;
}

void Aggs::Close()
{
    // 释放资源
    for (int i = 0; i < FLAGS_concurrency; i++) {
        curl_easy_cleanup(easy_handles_[i]);
        fclose(fps_[i]);
    }
    easy_handles_.clear();
    fps_.clear();

    curl_multi_cleanup(multi_handle_);
    curl_global_cleanup();
}

size_t Aggs::save(void *buffer, size_t size, size_t count, void *user_p)
{
    return fwrite(buffer, size, count, (FILE *)user_p);
}

