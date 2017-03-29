// main.cc (2015-05-15)
// Yan Gaofeng (yangaofeng@360.cn)

//==================================================================================
//实例化：一个通过使用具体值替换模板参数，从模板产生的普通类，
//函数或者成员函数的过程

//实例化演示(使用函数模板)
template<class T>
void swap(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}

//显示实例化：
template void swap<int>(); //无须给该函数重新编写函数体，这只是个声明, 注意：template后没有尖括号<>，函数名后有尖括号
//为什么要显示实例化？主要是提高编译器效率。
//template void swap<int>();声明相当于在本程序文件里有一个函数
//void swap(int &a, int &b) {
//  int temp;
//  temp = a;
//  a = b;
//  b = temp;
//}


//隐示实例化：
int i = 0;
int j = 1;
swap(i, j); //编译器根据参数i,j的类型隐式的生成swap<int>(int &a, int &b)的函数定义

//==================================================================================

//特化(具现化）：
//有些特殊情况，不能直接使用泛型模板展开实现，这里就要针对某个特殊的类型
//或者某一类特殊的类型，而实现一个特例模板
//上例swap函数，当T为一个struct 类型，它的交换就无法进行
//所以我们针对这种特殊情形，我们专门写了一个函数，只有当T为这种struct类型的时候
//才会调用这个特化函数

#define MAXNAME 128
struct job {
    char name[MAXNAME];
    int salary;
};

template <>
void swap <job> (job &a, job &b) { //函数模板显示特化（具现化），注意与实例化区分，必须有定义
    int salary;                     //注意template后<>为空，函数名swap后需要有一个<job>说明具体类型
    salary = a.salary;
    a.salary = b.salary;
    b.salary = salary;
}

//对类模板：
template <class T>
class Array {
private:
    T *ar;
    int l;
};

template class Array<int>; //类模板显示实例化

template <>
class Array<job> { //类模板显示特化（具现化），必须有定义，注意template后的<>为空， 类名Array后需要有一个<job>说明具体类型
private:
    job *ar;
    int l;
};


//偏特化：
//偏特化是指需要根据模板的"部分参数"进行特化

//类模板的偏特化
//以stl中的vector为例
//泛化版本
//template <class T, class Allocator>
//class vector {...}
//
//偏特化版本
//template <class Allocator>            //注意template后的尖括号中只有一个参数，而不是两个
//class vector<bool, Allocator> {...};  //类名vector后的尖括号中中有两个参数，bool就是特化的类型，Alloctor还是需要用户指定


