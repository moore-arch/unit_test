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

    }

// A helper function that some test uses.
static int toDouble(int n) {
    return 2*n;
}

// A helper function for testing Queue::Map().
void mapTester(const Queue<int> * q) {
    // Creates a new queue, where each element is twice as big as the
    // corresponding one in q.
    const Queue<int> * const new_q = q->map(toDouble);

    // Verifies that the new queue has the same size as q.
    ASSERT_EQ(q->size(), new_q->size());

    // Verifies the relationship between the elements of the two queues.
    for (const Node<int>*n1 = q->head(), *n2 = new_q->head();
         n1 != nullptr; n1 = n1->next(), n2 = n2->next()) {
        EXPECT_EQ(2 * n1->element(), n2->element());
    }

    delete new_q;
}

};


TEST_F(QueueTest, DefaultContructor) {
    EXPECT_EQ(0, q0_.size());
}


TEST_F(QueueTest, dequeue) {
    int *result = q0_.dequeue();
    EXPECT_TRUE(result == nullptr);

    result = q1_.dequeue();
    ASSERT_TRUE(result != nullptr);
    EXPECT_EQ(1, *result);
    EXPECT_EQ(0u, q1_.size());
    delete result;

    result = q2_.dequeue();
    ASSERT_TRUE(result != nullptr);
    EXPECT_EQ(2, *result);
    EXPECT_EQ(1u, q2_.size());
    delete result;
}


// Tests the Queue::Map() function.
TEST_F(QueueTest, Map) {
    mapTester(&q0_);
    mapTester(&q1_);
    mapTester(&q2_);
}
