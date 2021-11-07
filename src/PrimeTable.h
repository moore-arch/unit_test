//
// Created by shimeng on 2021/11/7.
//

#ifndef UNIT_TEST_PRIMETABLE_H
#define UNIT_TEST_PRIMETABLE_H
#include <algorithm>

class PrimeTable {
public:
    virtual ~PrimeTable() = default;

    virtual bool isPrime(int n) = 0;

    virtual int getNextPrime(int n) = 0;

};


class OnTheFlyPrimeTable: public PrimeTable {
public:
    bool isPrime(int n) override;

    int getNextPrime(int n) override;
};

class PreCalculatedPrimeTable: public PrimeTable {
private:
    int is_prime_size_;

    bool* is_prime_;

public:
    explicit PreCalculatedPrimeTable(int max): is_prime_size_(max + 1), is_prime_(new bool[max + 1]) { }

    ~PreCalculatedPrimeTable() override {
        delete[] is_prime_;
    }

    bool isPrime(int n) override;

    int getNextPrime(int n) override;

private:
    void calculatePrimeTable(int max);

    void operator=(const PreCalculatedPrimeTable &table) {};
};


#endif //UNIT_TEST_PRIMETABLE_H
