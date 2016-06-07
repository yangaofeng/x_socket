// main.cc (2016-06-07)
// Yan Gaofeng (yangaofeng@360.cn)

#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "./";

    LOG(INFO) << "hello world";

    return 0;
}
