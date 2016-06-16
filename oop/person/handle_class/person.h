// person.h (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>

class Person {
public:
    Person(const std::string &name, int age);
    ~Person();

    std::string name() const;
    int age() const;

private:
    class Impl;
    Impl *impl_;
};

#endif /*__PERSON_H__*/

