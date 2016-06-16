// person.cc (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include "person_impl.h"

Person::Impl::Impl(const std::string &name, int age)
    : name_(name), age_(age)
{
}

Person::Impl::~Impl()
{
}

std::string Person::Impl::name() const
{
    return name_;
}

int Person::Impl::age() const 
{
    return age_;
}

