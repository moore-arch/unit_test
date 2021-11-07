//
// Created by shimeng on 2021/11/7.
//

#include "QueueImpl.h"
#include "gtest/gtest.h"

class QueueTest: public testing::Test {
protected:
    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;

public:
    void SetUp() override {
        q1_.enqueue(1);
        q2_.enqueue(2);
        q2_.enqueue(3);
    }

    void TearDown() override {

    };
};

TEST_F(QueueTest, DefaultContructor) {
    EXPECT_EQ(0, q0_.size());
}

