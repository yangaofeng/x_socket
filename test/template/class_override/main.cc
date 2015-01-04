// main.cc (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <string>
#include <cstdlib>
//#include "stack1.hpp"
#include "stack2.hpp"

int main()
{
    try {
        Stack<int> intStack;
        Stack<std::string> stringStack;

        intStack.push(7);
        std::cout << intStack.top() << std::endl;

        stringStack.push(std::string("hello"));
        std::cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop();
    }
    catch (std::exception const &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

