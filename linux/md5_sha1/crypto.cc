#include <stdint.h>
#include <assert.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

#include "crypto.h"

#define  tolower(c)  __tolower(c)
#define  toupper(c)  __toupper(c)

static  inline unsigned char __tolower(unsigned char c)
{
    //判断字符c是否为大写英文字母 说明：当参数c为大写英文字母(A-Z)时，返回非零值，否则返回零。
    if (isupper(c))
        c -= 'A' - 'a' ;
    return c ;
}

static inline unsigned char __toupper(unsigned char c )
{
    //判断字符c是否为小写英文字母 说明：当参数c为小写英文字母(a-z)时，返回非零值，否则返回零。
    if (islower(c))
        c -= 'a' - 'A' ;
    return c ;
}

static int hex_to_bin(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
        return ch - '0';

    ch = tolower(ch) ;

    if ((ch >= 'a') && (ch <= 'f'))
        return ch - 'a' + 10;

    return -1;
}

void hex2bin(const char *hex_str, int str_len, std::string *bin)
{
    if (str_len <= 0 
            || str_len % 2 != 0 
            || bin == NULL) {
        return;
    }

    for (size_t i = 0; i < str_len; i += 2) {

        uint8_t x = 0;
        x = hex_to_bin(hex_str[i]);
        x <<= 4;
        x |= hex_to_bin(hex_str[i + 1]);

        bin->append(reinterpret_cast<const char *>(&x), 1);
    }
}

void bin2hex(const uint8_t *bin, int len, std::string *hexmd5)
{
    assert(bin != NULL);
    assert(len > 0);
    assert(hexmd5 != NULL);

    hexmd5->resize(len * 2);

    char* h = &((*hexmd5)[0]);

    uint8_t m = 0;
    // bin2hex
    for (size_t i = 0; i < len; ++i) {
        m = (bin[i] & 0xF0) >> 4;
        if (m <= 9) {
            h[i << 1] = m + '0';
        } else {
            h[i << 1] = m + 'a' - 10; 
        }   

        m = (bin[i]) & 0x0F;
        if (m <= 9) {
            h[(i << 1) + 1] = m + '0';
        } else {
            h[(i << 1) + 1] = m + 'a' - 10; 
        }   
    }   
}

void md5(const char* data, size_t len, std::string* hexmd5)
{
    assert(data != NULL);
    assert(len > 0);
    assert(hexmd5 != NULL);

    uint8_t bin16[16];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, len);
    MD5_Final(bin16, &ctx); 

    bin2hex(bin16, 16, hexmd5);
}

void md5_file(const char *filename, std::string *hexmd5)
{
    assert(filename != NULL);
    assert(hexmd5 != NULL);

    MD5_CTX ctx;
    unsigned char bin[16];
    char buffer[4096];
    int len = 0;
    int i;

    FILE *fp = NULL;

    memset(bin, 0, sizeof(bin));
    memset(buffer, 0, sizeof(buffer));

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("open file");
        return;
    }   

    MD5_Init(&ctx);
    while((len = fread(buffer, 1, 4096, fp)) > 0) {
        MD5_Update(&ctx, buffer, len);
        memset(buffer, 0, sizeof(buffer));
    }   

    MD5_Final(bin, &ctx);

    fclose(fp);

    bin2hex(bin, 16, hexmd5);
}


void sha1(const char* data, size_t len, std::string* hexsha1)
{
    assert(data != NULL);
    assert(len > 0);
    assert(hexsha1 != NULL);

    uint8_t bin[20];

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, data, len);
    SHA1_Final(bin, &ctx);

    bin2hex(bin, 20, hexsha1);

    return;
}

void sha1_file(const char *filename, std::string *hexsha1)
{
    assert(filename != NULL);
    assert(hexsha1!= NULL);

    SHA_CTX stx;
    unsigned char bin[20];//注意这里的字符个数为20
    char buffer[4096];
    int len = 0;
    int i;
    FILE * fp = NULL;
    memset(bin, 0, sizeof(bin));
    memset(buffer, 0, sizeof(buffer));
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("open file");
        return;
    }

    SHA1_Init(&stx);
    while((len = fread(buffer, 1, 4096, fp)) > 0) {
        SHA1_Update(&stx, buffer, len);
        memset(buffer, 0, sizeof(buffer));
    }
    SHA1_Final(bin,&stx);

    fclose(fp);

    bin2hex(bin, 20, hexsha1);
}

