// main.cc (2014-08-05)
// Yan Gaofeng (yangaofeng@360.cn)

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <tr1/unordered_map>
#include <vector>
#include <ext/pool_allocator.h>

using namespace std;

struct MyKey  {
    uint64_t h;
    uint64_t l;

    bool operator < (const MyKey & k) const  
    {
        return h < k.h;
    }  
};

struct hash_func {
    size_t operator()(const MyKey &k) const {
        return (size_t)k.h;
    }
};

struct cmp_func {
    bool operator()(const MyKey &k1, const MyKey &k2) const {
        return k1.h == k2.h;
    }
};

int main(int argc, char *argv[])
{
    cout << "MyKey size: " << sizeof(MyKey) << endl;

    //std::tr1::unordered_map<int, int> test;
    //std::tr1::unordered_map<uint64_t, uint64_t> test;
    //std::map<MyKey, uint64_t> test;
    //std::tr1::unordered_map<std::string, uint64_t> test;
    //std::map<std::string, uint64_t> test;
    //std::map<uint64_t, uint64_t> test;
    //std::vector<uint64_t> test;

    //std::tr1::unordered_map<MyKey, uint64_t, hash_func, cmp_func> test;
    std::tr1::unordered_map<MyKey, uint64_t, hash_func, cmp_func, __gnu_cxx::__pool_alloc<std::pair<MyKey, uint64_t> > > test;
    //std::tr1::unordered_map<std::string, uint64_t, tr1::hash<std::string>, std::equal_to<std::string>, __gnu_cxx::__pool_alloc<std::pair<std::string, uint64_t> > > test;

    //cout << "x size: " << x.size() << endl;
    //cout << "string object size: " << sizeof(std::string) << endl;

    for (uint64_t i = 0; i < 12000000; i++) {
        //std::string key;
        //key.append((char *)&i, 8);
        //key.append((char *)&i, 8);
        MyKey key;
        key.h = i;
        test[key] = i;
        //test.push_back(i);
    }

    cout << "unordered_map size: " << test.size() << endl;
    cout << "unordered_map value used types: " << test.size() * (sizeof(MyKey) + sizeof(uint64_t)) << endl;
    cout << "unordered_map bucket count: " << test.bucket_count() << endl;
    cout << "unordered_map bucket used bytes: " 
        << test.bucket_count() * (sizeof(size_t) + sizeof(void *) /*hash table element size*/) 
        << endl;

    getchar();

    return 0;
}

