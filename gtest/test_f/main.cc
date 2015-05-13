// main.cc (2015-05-13)
// Yan Gaofeng (yangaofeng@360.cn)

#include <gtest/gtest.h>
#include <iostream>

using namespace std;

class FooCalc {
public:
    void Init() { cout << "Init caled" << endl; }
    void Finalize() { cout << "Finalize called" << endl; }

    int Calc(int a, int b) {
        if (a == 0 || b == 0)
        {
            throw "don't do that";
        }
        int c = a % b;
        if (c == 0)
            return b;
        return Calc(b, c);
    }
};


class FooCalcTest : public testing::Test {
protected:
    FooCalcTest() {}
    ~FooCalcTest() {}

    virtual void SetUp() {
        foo_.Init();
    }

    virtual void TearDown() {
        foo_.Finalize();
    }

    FooCalc foo_;
};

TEST_F(FooCalcTest, HandleNoneZeroInput) {
    EXPECT_EQ(4, foo_.Calc(12, 16));
}

TEST_F(FooCalcTest, HandleNoneZeroInput_Error) {
    EXPECT_EQ(5, foo_.Calc(12, 16));
}
