//  Base64系列第三篇C/C++中使用Base64编码解码(使用boost库)
//  by MoreWindows( http://blog.csdn.net/MoreWindows )   
//  欢迎关注http://weibo.com/morewindows  
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

bool Base64Encode(const string& input, string* output) {
    typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<string::const_iterator, 6, 8> > Base64EncodeIterator;
    stringstream result;
    copy(Base64EncodeIterator(input.begin()) , Base64EncodeIterator(input.end()), ostream_iterator<char>(result));
    size_t equal_count = (3 - input.length() % 3) % 3;
    for (size_t i = 0; i < equal_count; i++) {
        result.put('=');
    }
    *output = result.str();
    return output->empty() == false;
}

bool Base64Decode(const string& input, string* output) {
    typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<string::const_iterator>, 8, 6> Base64DecodeIterator;
    stringstream result;
    try {
        copy(Base64DecodeIterator(input.begin()) , Base64DecodeIterator(input.end()), ostream_iterator<char>(result));
    } catch(...) {
        return false;
    }
    *output = result.str();
    return output->empty() == false;
}

int main()
{
    cout<<"    Base64系列第三篇C/C++中使用Base64编码解码(使用boost库)"<<endl;
    cout<<"  -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --"<<endl;
    cout<<" - http://blog.csdn.net/morewindows/article/details/11922519 -"<<endl;

    string input_str("MoreWindows - http://blog.csdn.net/morewindows?viewmode=contents ~!@#$%\r\n");
    string base64_str, output_str;

    cout<<"origin text: \n"<<input_str<<endl;

    Base64Encode(input_str, &base64_str);
    cout<<"encode: \n"<<base64_str<<endl;

    Base64Decode(base64_str, &output_str);
    cout<<"decode: \n"<<output_str<<endl;

    return 0;
}

