// main.cc (2015-06-01)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <string.h>
#include "crypto.h"

using namespace std;

int main(int argc, char *argv[])
{
    char buf[] = "hello world";
    const char *filename = "main.cc";

    cout << "string: " << buf << endl;
    cout << "filename: " << filename << endl;

    std::string hexmd5;
    md5(buf, strlen(buf), &hexmd5);
    cout << "string md5: " << hexmd5 << endl;
    md5_file(filename, &hexmd5);
    cout << "file md5: " << hexmd5 << endl;

    std::string hexsha1;
    sha1(buf, strlen(buf), &hexsha1);
    cout << "string sha1: " << hexsha1 << endl;
    sha1_file(filename, &hexsha1);
    cout << "file sha1: " << hexsha1 << endl;

    uint8_t bin[4] = {8, 9, 10, 11};
    std::string hex_str;
    bin2hex(bin, 4, &hex_str);
    cout << "8, 9, 10, 11 hex string: " << hex_str << endl;

    std::string ori_bin;
    hex2bin(hex_str.data(), hex_str.size(), &ori_bin);
    cout << "8, 9, 10, 11 ori string: ";
    for (int i = 0; i < 4; i++) {
        cout << (int)ori_bin[i] << " ";
    }
    cout << endl;

    return 0;
}

