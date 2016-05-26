#include <iostream>
#include <algorithm>

#include <school.pb.h>
#include <google/protobuf/text_format.h>

using namespace std;

struct Compare
{
    bool operator()(const Student &s1, const Student &s2) {
        return s1.score() > s2.score();
    }
};

int main(int argc, char *argv[])
{
    School school;
    //::google::protobuf::RepeatedPtrField<Student> *students;
    //students = school.mutable_students();
    Student *student;
    student = school.add_students();
    student->set_name("aaa");
    student->set_score(88);

    student = school.add_students();
    student->set_name("bbb");
    student->set_score(76);

    student = school.add_students();
    student->set_name("ccc");
    student->set_score(82);

    // Reorder the list of staff by pay scale
    std::sort(school.mutable_students()->begin(),
            school.mutable_students()->end(),
            Compare()
            );

    std::string str;
    google::protobuf::TextFormat::PrintToString(school, &str);

    cout << "max sort result: ------" << endl;
    cout << str << endl;

    cout << "remove last element result: ------" << endl;
    school.mutable_students()->RemoveLast();
    google::protobuf::TextFormat::PrintToString(school, &str);

    cout << str << endl;
}
