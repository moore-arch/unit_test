//
// Created by shimeng on 2021/11/7.
//
#include "Tools.h"
#include "QueueImpl.h"

#include <gtest/gtest.h>
#include <chrono>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <climits>

/**
 * gtest可以在测试正确性的同时添加时间限制
 *
 */


class QuickTest : public testing::Test {
private:
    std::chrono::high_resolution_clock::time_point start_time_;

protected:

    void SetUp() override {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    void TearDown() override {
        using namespace std::literals;
//        usleep(std::chrono::duration_cast<std::chrono::microseconds>(5ms).count());
//        usleep((5000ns).count());
        std::chrono::high_resolution_clock::time_point finish_time =
                std::chrono::high_resolution_clock::now();
        auto cost = finish_time - start_time_;
//        auto limit = std::chrono::milliseconds(5);
        EXPECT_LE(cost, 5ms)
                            << fmt::format("cost too long, execute time: {}\n", cost);
    }
};

class IntegerFunctionTest : public QuickTest {

};


TEST_F(IntegerFunctionTest, factorial) {
    EXPECT_EQ(Tools::factorial(0), 1);

    EXPECT_EQ(Tools::factorial(-1), 1);
    EXPECT_EQ(Tools::factorial(-10), 1);

    // Tests factorial of 0.
    EXPECT_EQ(Tools::factorial(0), 1);

    // Tests factorial of positive numbers.
    EXPECT_EQ(Tools::factorial(1), 1);
    EXPECT_EQ(Tools::factorial(2), 2);
    EXPECT_EQ(Tools::factorial(3), 6);
    EXPECT_EQ(Tools::factorial(8), 40320);
}


TEST_F(IntegerFunctionTest, IsPrime) {
    // Tests negative input.
    EXPECT_FALSE(Tools::isPrime(-1));
    EXPECT_FALSE(Tools::isPrime(-2));
    EXPECT_FALSE(Tools::isPrime(INT_MIN));

    // Tests some trivial cases.
    EXPECT_FALSE(Tools::isPrime(0));
    EXPECT_FALSE(Tools::isPrime(1));
    EXPECT_TRUE(Tools::isPrime(2));
    EXPECT_TRUE(Tools::isPrime(3));

    // Tests positive input.
    EXPECT_FALSE(Tools::isPrime(4));
    EXPECT_TRUE(Tools::isPrime(5));
    EXPECT_FALSE(Tools::isPrime(6));
    EXPECT_TRUE(Tools::isPrime(23));
}


class QueueQuickTest : public QuickTest {
protected:
    void SetUp() override {
        // First, we need to set up the super fixture (QuickTest).
        QuickTest::SetUp();

        // Second, some additional setup for this fixture.
        q1_.enqueue(1);
        q2_.enqueue(2);
        q2_.enqueue(3);
    }

    // By default, TearDown() inherits the behavior of
    // QuickTest::TearDown().  As we have no additional cleaning work
    // for QueueTest, we omit it here.
    //
    // virtual void TearDown() {
    //   QuickTest::TearDown();
    // }

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};


// tests using the QueueQuickTest fixture.
TEST_F(QueueQuickTest, defaultConstructorQuick) {
    EXPECT_EQ(0u, q0_.size());
}

TEST_F(QueueQuickTest, dequeueQuick) {
    int *n = q0_.dequeue();
    EXPECT_TRUE(n == nullptr);

    n = q1_.dequeue();
    EXPECT_TRUE(n != nullptr);

    EXPECT_EQ(1, *n);
    EXPECT_EQ(0u, q1_.size());
    delete n;

    n = q2_.dequeue();
    EXPECT_TRUE(n != nullptr);
    EXPECT_EQ(2, *n);
    EXPECT_EQ(1u, q2_.size());
    delete n;
}
