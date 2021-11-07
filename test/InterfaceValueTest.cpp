//
// Created by shimeng on 2021/11/7.
//

#include "PrimeTable.h"

#include <gtest/gtest.h>

typedef PrimeTable* createPrimeTable();

PrimeTable* CreateOnTheFlyPrimeTable() {
    return new OnTheFlyPrimeTable();
}

template <size_t max_precalculated>
PrimeTable* CreatePreCalculatedPrimeTable() {
    return new PreCalculatedPrimeTable(max_precalculated);
}


class PrimeTableValueTest : public testing::TestWithParam<createPrimeTable*> {
public:
    ~PrimeTableValueTest() override { delete table_; }
    void SetUp() override { table_ = (*GetParam())(); }
    void TearDown() override {
        delete table_;
        table_ = nullptr;
    }

protected:
    PrimeTable* table_;
};

TEST_P(PrimeTableValueTest, ReturnsFalseForNonPrimes) {
    EXPECT_FALSE(table_->isPrime(-5));
    EXPECT_FALSE(table_->isPrime(0));
    EXPECT_FALSE(table_->isPrime(1));
    EXPECT_FALSE(table_->isPrime(4));
    EXPECT_FALSE(table_->isPrime(6));
    EXPECT_FALSE(table_->isPrime(100));
}




INSTANTIATE_TEST_SUITE_P(OnTheFlyAndPreCalculated, PrimeTableValueTest,
                         testing::Values(&CreateOnTheFlyPrimeTable,
                                &CreatePreCalculatedPrimeTable<1000>));