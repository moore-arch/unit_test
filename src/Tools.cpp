//
// Created by shimeng on 2021/11/7.
//

#include "Tools.h"


int Tools::factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}

bool Tools::isPrime(int n) {
    if (n <= 1)
        return false;
    if (n % 2 == 0)
        return n == 2;

    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}
