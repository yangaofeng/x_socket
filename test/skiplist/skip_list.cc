// skip_list.cc (2015-01-24)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "skip_list.h"

using namespace std;

SkipList::SkipList() 
    : level_(0),
    size_(0),
    header_(AllocNode(kMaxLevel - 1)), 
    nil_(AllocNode(0)),
    rnd_(0xdeadbeef)
{
    nil_->key = 0x7fffffff;

    for (int i = 0; i < kMaxLevel; i++) {
        header_->forward[i] = nil_;
    }

    header_->level = kMaxLevel - 1;

    srandom(time(NULL));
}

SkipList::~SkipList()
{
    //release skiplist
    for (Node *node = header_; node != nil_; node = node->forward[0]) {
        FreeNode(node);
    }

    FreeNode(nil_);

    header_ = NULL;
    nil_ = NULL;
}

int SkipList::RandomLevel()
{
    int level = 0;

#if 1
    //借鉴leveldb的算法，利用概率控制不同level节点的分布
    //
    //while ((level < (kMaxLevel - 1)) && (random() % 4 == 0)) {
    //    level++;
    //}
    while ((level < (kMaxLevel - 1)) && (rnd_.Next() % 4 == 0)) {
        level++;
    }
#else

    level = random() % (kMaxLevel - 1);
#endif

    cout << "skip list: random level: " << level << endl;

    return level;
}

SkipList::Node *SkipList::AllocNode(int level)
{
    assert(level < kMaxLevel);

    //level's range: 0 ~ kMaxLevel - 1
    Node *node = (Node *)malloc(sizeof(Node) + level * sizeof(Node *));
    assert(node != NULL);

    return node;
}

void SkipList::FreeNode(Node *node)
{
    assert(node != NULL);

    free(node);
}

bool SkipList::Insert(Key key, Value value)
{
    Node *update[kMaxLevel];

    Node *x = header_;

    //在第i层上查找key所要插入的位置, 一直找到第0层
    //因为只有第0层可以插入key
    for (int i = level_; i >= 0; i--) {

        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }

        //保存大于key的位置信息
        //note: 见下边的for循环中的update节
        update[i] = x;
    }

    //x指向大于key的节点
    x = x->forward[0];
    if (x->key == key) {
        //update and return
        x->value = value;
        return false;
    }

    int l = RandomLevel();
    if (l > level_) {
        level_++;
        l = level_;
        update[l] = header_;
    }

    Node *node = AllocNode(l);
    assert(node != NULL);
    node->key = key;
    node->level = l;
    node->value = value;

    for (int i = l; i >= 0; i--) {
        x = update[i];
        //update: 新节点的forward指向大于key的位置
        node->forward[i] = x->forward[i];
        x->forward[i] = node;
    }

    size_++;

    return true;
}

bool SkipList::Delete(Key key, Value *value)
{
    assert(value != NULL);

    Node *update[kMaxLevel];
    Node *x = header_;

    for (int i = level_; i >= 0; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }

        update[i] = x;
    }

    x = x->forward[0];

    if (x->key != key) {
        return false;
    }

    *value = x->value;

    for (int i = level_; i >= 0; i--) {
        if (update[i]->forward[i] != x) {
            break;
        }

        update[i]->forward[i] = x->forward[i];
    }

    FreeNode(x);


    //更新level的值
    while (level_ > 0 && header_->forward[level_] == nil_) {
        level_--;
    }

    size_--;

    return true;
}

bool SkipList::Search(Key key, Value *value)
{
    assert(value != NULL);

    Node *x = header_;
    for (int i = level_; i >= 0; i--) {
        while (x->forward[i]->key < key) {
            cout << "list level: "
                << level_
                << ", searched key: " 
                << x->forward[i]->key
                << ", searched value: " 
                << x->forward[i]->value
                << ", searched level: " << x->forward[i]->level
                << endl;
            x = x->forward[i];
        }
    }

    x = x->forward[0];

    if (x->key == key) {
        *value = x->value;
        return true;
    } else {
        return false;
    }
}

void SkipList::Iterator::Next()
{
    if (node_ != list_.nil_) {
        node_ = node_->forward[0];
    }
}

bool SkipList::Iterator::Valid() const
{
    return node_ != list_.nil_;
}

Key SkipList::Iterator::key() const
{
    return node_->key;
}

Value SkipList::Iterator::value() const
{
    return node_->value;
}

Value SkipList::Iterator::level() const
{
    return node_->level;
}

