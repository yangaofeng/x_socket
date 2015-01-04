// stack1.hpp (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __STACK1_HPP__
#define __STACK1_HPP__

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
    private:
        std::vector<T> elems;
    public:
        void push(T const &);
        void pop();
        T top() const;
        bool empty () {
            return elems.empty();
        }

};

template <typename T>
void Stack<T>::push(T const &elem)
{
    elems.push_back(elem);
}

template <typename T>
void Stack<T>::pop()
{
    if (elems.empty()) {
        throw std::out_of_range("empty stack on pop");
    }

    elems.pop_back();
}

template <typename T>
T Stack<T>::top() const
{
    if (elems.empty()) {
        throw std::out_of_range("empty stack on top");
    }

    return elems.back();
}

#endif /*__STACK1_HPP__*/

