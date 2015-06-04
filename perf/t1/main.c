
//
//用stat命令观察大致的热点
//perf stat ./t1
//
//用下边的命令取得report 要分析的数据
//perf record -e cpu-clock -g ./t1
//用下边的命令分析recore生成的数据
//perf report
//
//
void longa() 
{ 
    int i,j; 
    for(i = 0; i < 10000000; i++) 
        j=i; //am I silly or crazy? I feel boring and desperate. 
} 

void foo2() 
{ 
    int i; 
    for(i=0 ; i < 10; i++) 
        longa(); 
} 

void foo1() 
{ 
    int i; 
    for(i = 0; i< 100; i++) 
        longa(); 
} 

int main(void) 
{ 
    foo1(); 
    foo2(); 
}
