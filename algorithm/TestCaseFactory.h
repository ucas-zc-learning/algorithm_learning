#ifndef __TEST_CASE_FACTORY__
#define __TESE_CASE_FACTORY__

#include "RbTreeTest.h"

namespace NS_FACTORY
{
    static const int RB_TREE = 12;                // Chapter-13, RbTree index
    static const int ALGORITHM_END = 13;          // index end
}

class TestCaseFactory
{
private:
    /* data */
public:
    TestCaseFactory(/* args */);
    ~TestCaseFactory();
    static TestCaseBase *CreateObject(int index);
};


#endif