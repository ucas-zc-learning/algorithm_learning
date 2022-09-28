#include "TestCaseFactory.h"

TestCaseFactory::TestCaseFactory()
{}

TestCaseFactory::~TestCaseFactory()
{}

TestCaseBase *TestCaseFactory::CreateObject(int index)
{
    TestCaseBase *object = nullptr;
    
    switch (index)
    {
    case NS_FACTORY::RB_TREE:
        object = new RbTreeTest();
        break;
    
    default:
        object = nullptr;
        break;
    }

    return object;
}