// dispatch.cc (2015-06-11)
// Yan Gaofeng (yangaofeng@360.cn)

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

bool LogDispatchInit(const char* conf)
{
    assert(conf != NULL);

    printf("config file: %s\n", conf);
    return true;
}

void LogDispatchProcess(const struct LogAttr* attr,  const char* log_data, unsigned int log_len)
{
    assert(attr != NULL);
    assert(log_data != NULL);
    assert(log_len > 0);

    //while (true) {
        usleep(1000);
        //printf("log len: %d\n", log_len);
    //}
}

#ifdef __cplusplus
}
#endif /*__cplusplus*/

