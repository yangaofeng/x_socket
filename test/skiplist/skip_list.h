// list.h (2015-01-22)
// Yan Gaofeng (yangaofeng@360.cn)

#include "random.h"

typedef int Key;
typedef int Value;

class SkipList {
public:
    SkipList();
    ~SkipList();

    enum {
        kMaxLevel = 12
    };

    struct Node {
        Key key;
        Value value;
        int level;
        Node *forward[1]; //At least one level
    };

    class Iterator {
    public:
        Iterator(const SkipList &list) 
            : list_(list), node_(list.header_->forward[0]) {}

        ~Iterator() {}

        bool Valid() const;
        void Next();

        Key key() const;
        Value value() const;
        int level() const;

    private:
        const SkipList &list_;
        Node *node_;
    };

    bool Insert(Key key, Value value);
    bool Delete(Key key, Value *value);
    bool Search(Key key, Value *value);

private:
    int RandomLevel();
    static Node *AllocNode(int level);
    static void FreeNode(Node *node);

private:
    int level_;
    int size_;
    Node *header_;
    Node *nil_;
    Random rnd_;
};

