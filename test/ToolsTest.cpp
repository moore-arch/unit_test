//
// Created by shimeng on 2021/11/7.
//

#include "Tools.h"

#include <gtest/gtest.h>
#include <climits>

/**
 * This test is named "Negative", and belongs to the "FactorialTest"
 *
 * https://github.com/google/googletest/blob/master/googletest/samples/sample1_unittest.cc
 */
TEST(FactorialTest, Negative) {
    EXPECT_EQ(1, Tools::factorial(-5));
    EXPECT_EQ(1, Tools::factorial(-1));
    EXPECT_GT(Tools::factorial(-10), 0);
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) {
    EXPECT_EQ(1, Tools::factorial(0));
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
    EXPECT_EQ(1, Tools::factorial(1));
    EXPECT_EQ(2, Tools::factorial(2));
    EXPECT_EQ(6, Tools::factorial(3));
    EXPECT_EQ(40320, Tools::factorial(8));
}


// Tests Tools::isPrime()

// Tests negative input.
TEST(IsPrimeTest, Negative) {
    // This test belongs to the IsPrimeTest test case.

    EXPECT_FALSE(Tools::isPrime(-1));
    EXPECT_FALSE(Tools::isPrime(-2));
    EXPECT_FALSE(Tools::isPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
    EXPECT_FALSE(Tools::isPrime(0));
    EXPECT_FALSE(Tools::isPrime(1));
    EXPECT_TRUE(Tools::isPrime(2));
    EXPECT_TRUE(Tools::isPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
    EXPECT_FALSE(Tools::isPrime(4));
    EXPECT_TRUE(Tools::isPrime(5));
    EXPECT_FALSE(Tools::isPrime(6));
    EXPECT_TRUE(Tools::isPrime(23));
}

TEST_F(FactorialTest_Positive_Test, h) {
    EXPECT_FALSE(Tools::isPrime(4));

}
