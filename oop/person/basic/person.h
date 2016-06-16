// person.h (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include <string>

class Person {
public:
    Person(const std::string &name, int age);
    ~Person();

    std::string name() const;
    int age() const;

private:
    std::string name_;
    int age_;
};

