// real_person.h (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __REAL_PERSON_H__
#define __REAL_PERSON_H__

#include <string>
#include "person.h"

class RealPerson : public Person {
public:
    RealPerson(const std::string &name, int age);
    virtual ~RealPerson();

    virtual std::string name() const;
    virtual int age() const;

private:
    std::string name_;
    int age_;
};

#endif /*__REAL_PERSON_H__*/
