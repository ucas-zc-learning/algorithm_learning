#ifndef __TEST_CASE_H__
#define __TEST_CASE_H__

#include <iostream>

class TestCaseBase
{
private:
    /* data */
public:
    TestCaseBase(/* args */) {}
    ~TestCaseBase() {}

    virtual int TestCase() {}
};


#endif