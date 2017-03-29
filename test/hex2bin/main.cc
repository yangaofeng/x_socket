#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <iostream>
#include <string>

#include <stdint.h>

#define  tolower(c)  __tolower(c)
#define  toupper(c)  __toupper(c)

using namespace std;

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

int hex_to_bin(char ch)
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

        uint8_t tmp = 0;
        tmp = hex_to_bin(hex_str[i]);
        tmp <<= 4;
        tmp |= hex_to_bin(hex_str[i + 1]);

        bin->append(reinterpret_cast<const char *>(&tmp), 1);
    }
}


int main(void)
{
    printf("%d\n",hex_to_bin('1'));
    printf("%d\n",hex_to_bin('f'));
    printf("%d\n",hex_to_bin('a'));
    printf("%d\n",hex_to_bin('9'));

    printf("%p\n",hex_to_bin('1'));
    printf("%p\n",hex_to_bin('f'));
    printf("%p\n",hex_to_bin('a'));
    printf("%p\n",hex_to_bin('9'));

    char buf[] = "0A0B0C";

    std::string bin;
    hex2bin(buf, 6, &bin);
    if (bin.empty()) {
        std::cout << "hex 2 bin failed" << std::endl;
        return -1;
    }

    for (int i = 0; i < bin.size(); i++) {
        printf("%d ", (int)(bin[i]));
    }
    printf("\n");

    return 0 ;
}

