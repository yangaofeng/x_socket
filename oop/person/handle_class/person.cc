// person.cc (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include "person.h"
#include "internal/person_impl.h"

Person::Person(const std::string &name, int age)
    : impl_(new Impl(name, age))
{
}

Person::~Person()
{
    if (impl_ != NULL) {
        delete impl_;
    }
}

std::string Person::name() const
{
    return impl_->name();
}

int Person::age() const 
{
    return impl_->age();
}

