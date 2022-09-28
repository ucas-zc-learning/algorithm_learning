#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <iostream>

namespace NS_RBTREE {
    // 红色结点标记
    static const int RED = 0;
    // 黑色结点标记
    static const int BLACK = 1;

    // 执行成功返回值
    static const int OK = 0;
    // 执行失败返回值
    static const int FAIL = -1;

    // 红黑树结点定义
    class RbNode
    {
    public:
        /* data */
        int key;
        int color;
        NS_RBTREE::RbNode *left;
        NS_RBTREE::RbNode *right;
        NS_RBTREE::RbNode *parent;

    public:
        RbNode(/* args */)
        {
            key = 0;
            color = NS_RBTREE::RED;
            left = nullptr;
            right = nullptr; 
            parent = nullptr;
        }

        ~RbNode()
        {}
    };
}


class RbTree
{
private:
    /* data */

public:
    RbTree(/* args */);
    ~RbTree();
    int RbTreeInsert(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node);
    int RbTreeDelete(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node);
    NS_RBTREE::RbNode *RbTreeSearch(NS_RBTREE::RbNode *root, int key);

private:
    void LeftRotate(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *cur);
    void RightRotate(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *cur);
    int RbTreeInsertFixUp(NS_RBTREE::RbNode *&root, NS_RBTREE::RbNode *node);
    int RbTreeDeleteFixUp(NS_RBTREE::RbNode *&root, 
                    NS_RBTREE::RbNode *child, NS_RBTREE::RbNode *parent);
};

#endif