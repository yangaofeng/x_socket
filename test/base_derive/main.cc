// main.cc (2015-05-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

using namespace std;

//演示 quakedb项目中，quake/net下tcp transport 继承关系中 DerivedT的用法
//必须用template方法，直接使用派生类行不能，提示incomplete type错误

template<int F>
class BasicTransport;

template<class DeriveT = BasicTransport<1> >
class StreamTransportBase {
public:
    StreamTransportBase () {}
    ~StreamTransportBase() {}

    void DoCall() {
        static_cast<DeriveT *>(this)->Call();
        //Call();
    }

protected:
    void Call() {
        cout << "hello Stream" << endl;
    }
};

class TcpTransportBase: public StreamTransportBase<> {
    friend class StreamTransportBase<>;
private:
    void Call() {
        cout << "hello Tcp" << endl;
    }
};

template<>
class BasicTransport<1>: public TcpTransportBase {
};

typedef BasicTransport<1> Tcp;

int main()
{
    Tcp t;
    t.DoCall();

    return 0;
}

