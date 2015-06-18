// dispatch.h (2015-06-11)
// Yan Gaofeng (yangaofeng@360.cn)

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

struct LogAttr {
    int a;
    int b;
};

bool LogDispatchInit(const char* conf);
void LogDispatchProcess(const struct LogAttr* attr,  const char* log_data, unsigned int log_len)

#ifdef __cplusplus
}
#endif /*__cplusplus*/

