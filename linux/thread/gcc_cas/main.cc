#include <iostream>
using namespace std;

int main()
{
    bool lock(false);
    bool old_value = __sync_val_compare_and_swap( &lock, false, true); 
    cout << lock << endl; // prints 0x1
    cout << old_value << endl; // prints 0x0

    return 0;
}
