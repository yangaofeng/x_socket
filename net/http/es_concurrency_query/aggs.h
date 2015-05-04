#ifndef __AGGS_H__
#define __AGGS_H__

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <vector>

class Aggs {
public: 
    Aggs() 
        : multi_handle_(NULL)
    {}

    ~Aggs() { Close(); }

    bool Init();
    void Run();

private:
    static size_t save(void *buffer, size_t size, size_t count, void *user_p);
    void Close();
    void UsedTime();

private:
    CURLM *multi_handle_;
    std::vector<CURL *> easy_handles_;
    std::vector<FILE *> fps_;

    std::string url_;
    std::string query_;
};

#endif //__AGGS_H__

