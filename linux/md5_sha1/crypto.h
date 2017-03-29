// md5.h (2015-06-01)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __OPENSSL_MD5_WRAPPER_H__
#define __OPENSSL_MD5_WRAPPER_H__

#include <stdint.h>
#include <string>

void bin2hex(const uint8_t *bin, int len, std::string *hexmd5);
void hex2bin(const char *str, int str_len, std::string *bin);

void md5(const char* data, size_t len, std::string* hexmd5);
void md5_file(const char *filename, std::string *hexmd5);
void sha1(const char* data, size_t len, std::string* hexsha1);
void sha1_file(const char *filename, std::string *hexmd5);

#endif /*__OPENSSL_MD5_WRAPPER_H__*/

