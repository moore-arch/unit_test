//
// Created by shimeng on 2021/11/7.
//

#include "PrimeTable.h"

#include <gtest/gtest.h>

/**
 * reference: https://github.com/google/googletest/blob/master/googletest/samples/sample6_unittest.cc
 *
 * This sample shows how to test common properties of multiple
 * implementations of the same interface (aka interface tests).
 */

template <typename T>
PrimeTable* createPrimeTable();

template <>
PrimeTable* createPrimeTable<OnTheFlyPrimeTable>() {
    return new OnTheFlyPrimeTable();
}

template <>
PrimeTable* createPrimeTable<PreCalculatedPrimeTable>() {
    return new PreCalculatedPrimeTable(10000);
}

template <typename T>
class PrimeTableTest: public testing::Test {
protected:
    // Note that we test an implementation via the base interface
    // instead of the actual implementation class.  This is important
    PrimeTable *table_;

    PrimeTableTest(): table_(createPrimeTable<T>()) {}

    ~PrimeTableTest() override {
        delete table_;
    }

};

// To write a typed test case, first use
//
//   TYPED_TEST_SUITE(TestCaseName, TypeList);
//
// to declare it and specify the type parameters.  As with TEST_F,
// TestCaseName must match the test fixture name.

typedef testing::Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable> Implementations;

TYPED_TEST_SUITE(PrimeTableTest, Implementations);

// Then use TYPED_TEST(TestCaseName, TestName) to define a typed test,
TYPED_TEST(PrimeTableTest, nonPrime) {
    EXPECT_FALSE(this->table_->isPrime(-5));
    EXPECT_FALSE(this->table_->isPrime(0));
    EXPECT_FALSE(this->table_->isPrime(1));
    EXPECT_FALSE(this->table_->isPrime(4));
    EXPECT_FALSE(this->table_->isPrime(6));
    EXPECT_FALSE(this->table_->isPrime(100));
}


template <class T>
class PrimeTableTest2 : public PrimeTableTest<T> {
};
TYPED_TEST_SUITE_P(PrimeTableTest2);

TYPED_TEST_P(PrimeTableTest2, nonPrime) {
    EXPECT_FALSE(this->table_->isPrime(-5));
    EXPECT_FALSE(this->table_->isPrime(0));
    EXPECT_FALSE(this->table_->isPrime(1));
    EXPECT_FALSE(this->table_->isPrime(4));
    EXPECT_FALSE(this->table_->isPrime(6));
    EXPECT_FALSE(this->table_->isPrime(100));
}

REGISTER_TYPED_TEST_SUITE_P(
        PrimeTableTest2,  // The first argument is the test case name.
// The rest of the arguments are the test names.
        nonPrime /*, *other test names*/);


typedef testing::Types<OnTheFlyPrimeTable, PreCalculatedPrimeTable>
        PrimeTableImplementations;

INSTANTIATE_TYPED_TEST_SUITE_P(OnTheFlyAndPreCalculated,    /* Instance name */
                               PrimeTableTest2,             /* Test case name */
                               PrimeTableImplementations);  /* Type list */
//INSTANTIATE_TYPED_TEST_SUITE_P(OnTheFlyAndPreCalculated,
//                               PrimeTableTest2,
//                               PrimeTableImplementations);
