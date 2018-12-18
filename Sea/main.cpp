#include <iostream>
#include "../Sea/Test/TestLog.h"
#include <gtest/gtest.h>
using namespace std;


TEST(FunTest, HandleZeroInput)
{
    EXPECT_EQ(1, add(0));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
