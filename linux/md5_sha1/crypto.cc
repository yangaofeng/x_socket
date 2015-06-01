#include <stdint.h>
#include <assert.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

#include "crypto.h"

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

