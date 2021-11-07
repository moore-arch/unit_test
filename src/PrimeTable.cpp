//
// Created by shimeng on 2021/11/7.
//

#include <complex>
#include "PrimeTable.h"

bool OnTheFlyPrimeTable::isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= std::sqrt(n); ++i) {
        if ((n % i) == 0)
            return false;
    }
    return true;
}

int OnTheFlyPrimeTable::getNextPrime(int n) {
    if (n < 0) {
        return -1;
    }

    for (int i = n + 1; i < INT32_MAX; ++i) {
        if (isPrime(i))
            return i;
    }
    return -1;
}


bool PreCalculatedPrimeTable::isPrime(int n) {
    return 0 <= n && n <= is_prime_size_ && is_prime_[n];
}

int PreCalculatedPrimeTable::getNextPrime(int n) {
    for (int idx = n + 1; idx < is_prime_size_; ++idx) {
        if (is_prime_[idx]) {
            return idx;
        }
    }
    return -1;
}

void PreCalculatedPrimeTable::calculatePrimeTable(int max) {
    std::fill(is_prime_, is_prime_ + is_prime_size_, true);
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i = 2; i <= is_prime_size_; ++i) {
        if (!is_prime_[i])
            continue;

        for (int j = i * i; j <= max; ++j) {
            is_prime_[j] = false;
        }
    }

}

