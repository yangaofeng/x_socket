// main.cc (2015-03-03)
// Yan Gaofeng (yangaofeng@360.cn)

/*
 * refurl: http://blog.csdn.net/morewindows/article/details/6684558
 * */

#include <iostream>

using namespace std;

int adjust_array(int a[], int l, int r)
{
    int i = l;
    int j = r;
    int x = a[l];

    while (i < j) {
        while (i < j && a[j] >= x) {
            j--;
        }
        if (i < j) {
            a[i] = a[j];
            i++;
        }

        while (i < j && a[i] < x) {
            i++;
        }
        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }

    a[i] = x;

    return i;
}

void quick_sort(int a[], int l, int r)
{
    if (l < r) {
        int i = adjust_array(a, l, r);
        quick_sort(a, 0, i - 1);
        quick_sort(a, i + 1, r);
    }
}

int main(int argc, char *argv[])
{
    int a[] = {72,6,57,88,60,42,83,73,48,85};
    quick_sort(a, 0, 9);

    for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
        cout << a[i] << "," << endl;
    }
    
    return 0;
}
