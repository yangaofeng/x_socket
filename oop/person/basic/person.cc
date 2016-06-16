// person.cc (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include "person.h"

Person::Person(const std::string &name, int age)
    : name_(name), age_(age)
{
}

Person::~Person()
{
}

std::string Person::name() const
{
    return name_;
}

int Person::age() const 
{
    return age_;
}

