// accumtraits2.h (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char> {
public:
    typedef int AccT;
    static const AccT zero = 0;
};

template <>
class AccumulationTraits<short> {
    public:
        typedef short AccT;
        static const AccT zero = 0;
};

template <>
class AccumulationTraits<int> {
    public:
        typedef long AccT;
        static const AccT zero = 0;
};

template <>
class AccumulationTraits<unsigned int> {
    public:
        typedef unsigned long AccT;
        static const AccT zero = 0;
};

template <>
class AccumulationTraits<float> {
    public:
        typedef double AccT;
        static const AccT zero = 0.0;
};

