#include <iostream>
#include "stack.h"

using namespace std;

int main()
{

    try {
        Stack<int> int_s;
        Stack<string> string_s;
        int_s.Push(7);
        cout << int_s.Top() << endl;

        string_s.Push("Hello");
        cout << string_s.Top() << endl; 

        int_s.Pop();
        string_s.Pop();
    } catch (std::exception const &ex) {
        cerr << "Exception: " << ex.what() << endl;
    }

    return  0;
}

