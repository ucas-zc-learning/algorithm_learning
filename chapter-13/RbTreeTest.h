#ifndef __RBTREE_TEST_H__
#define __RBTREE_TEST_H__

#include "TestCaseBase.h"
#include "RbTree.h"
#include <vector>

#define TEST_OK 0
#define TEST_FAIL -1

#define MAX_SIZE 128

class RbTreeTest : public TestCaseBase
{
private:
    /* data */
    RbTree *obj;
    NS_RBTREE::RbNode *root;

public:
    RbTreeTest(/* args */);
    ~RbTreeTest();

    int TestCase();

private:
    int Level(std::vector<int> _data, std::vector<int> _color);
    int SearchAndDelete(int key);
};

#endif