// person.h (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef _PERSON_H__
#define _PERSON_H__

#include <string>

class Person {
public:
    virtual ~Person() {}

    virtual std::string name() const = 0;
    virtual int age() const = 0;
};

#endif /*__PERSON_H__*/

