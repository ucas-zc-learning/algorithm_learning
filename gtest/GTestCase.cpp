#include "TestCaseFactory.h"
#include "gtest/gtest.h"

namespace 
{
    class TestAlgorithm : public testing::Test
    {
        void SetUp() override
        {};

        void TearDown() override
        {};
    };
}

TEST_F(TestAlgorithm, TEST_ALGORITHM)
{
    for (int index = 0; index < NS_FACTORY::ALGORITHM_END; ++index)
    {
        TestCaseBase * obj = TestCaseFactory::CreateObject(index);
        if (obj == nullptr)
            continue;

        ASSERT_EQ(TEST_OK, obj->TestCase());
    }
}