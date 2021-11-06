//
// Created by shimeng on 2021/11/6.
//

#include "gtest/gtest.h"
#include "fmt/core.h"


/**
 * gtest 的入口函数，使用gtest_main代替gtest连接库可以不写入口函数
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
