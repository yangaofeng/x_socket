// person.h (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __PERSON_IMPL_H__
#define __PERSON_IMPL_H__

#include "person.h"

class Person::Impl {
public:
    Impl(const std::string &name, int age);
    ~Impl();

    std::string name() const;
    int age() const;

private:
    std::string name_;
    int age_;
};

#endif /*__PERSON_IMPL_H__*/

