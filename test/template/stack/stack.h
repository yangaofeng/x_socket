// stack.h (2014-08-18)
// Yan Gaofeng (yangaofeng@360.cn)

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
    private:
        std::vector<T> elems_;

    public:
        void Push(T const &);
        void Pop();
        T Top() const;
        bool empty() const {
            return elems_.empty();
        }
};

template <typename T>
void Stack<T>::Push(T const &elem)
{
    elems_.push_back(elem);
}

template <typename T>
void Stack<T>::Pop()
{
    if (elems_.empty()) {
        throw std::out_of_range("Stack<>::Pop: empty stack");
    }

    elems_.pop_back();
}

template <typename T>
T Stack<T>::Top() const
{
    if (elems_.empty()) {
        throw std::out_of_range("Stack<>::Pop: empty stack");
    }

    return elems_.back();
}

