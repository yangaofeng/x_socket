// stack2.hpp (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __STACK2_HPP__
#define __STACK2_HPP__

#include <deque>
#include <string>
#include <stdexcept>

#include "stack1.hpp"

template <>
class Stack<std::string> {
    private:
        std::deque<std::string> elems;

    public:
        void push(std::string const &);
        void pop();
        std::string top() const;
};

void Stack<std::string>::push(std::string const &elem)
{
    elems.push_back(elem);
}

void Stack<std::string>::pop()
{
    if (elems.empty()) {
        throw std::out_of_range("empty string stack on pop");
    }

    elems.pop_back();
}

std::string Stack<std::string>::top() const
{
    if (elems.empty()) {
        throw std::out_of_range("empty string stack on top");
    }

    return elems.back();
}

#endif /*__STACK2_HPP__*/

