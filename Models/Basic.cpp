//
//  Basic.cpp
//  MathTools
//
//  Created by Richard Chien on 6/29/15.
//
//

#include "Basic.h"

using namespace std;

bool isInt(double a) {
    double dif = fabs(((long)a - a));
    if(dif < 0.00000001 || dif > 0.9999999)
        return true;
    else
        return false;
}

long commonDivisorOf(long u, long v) {
    long temp;
    while (v != 0) {
        temp = u % v;
        u = v;
        v = temp;
    }
    return u;
}

long commonMultipleOf(long u, long v) {
    long commonDiv = commonDivisorOf(u, v);
    return (u > v ? u : v) / commonDiv * (u < v ? u : v);
}

long commonDivisorOf(long a, long b, long c) {
    long commonDivisor = commonDivisorOf(a, b);
    commonDivisor = commonDivisorOf(commonDivisor, c);
    return commonDivisor;
}

long commonMultipleOf(long a, long b, long c) {
    long commonMultiple = commonMultipleOf(a, b);
    commonMultiple = commonMultipleOf(commonMultiple, c);
    return commonMultiple;
}

long commonDivisorOf(vector<long> nums) {
    long commonDivisor = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        commonDivisor = commonDivisorOf(commonDivisor, nums[i]);
    }
    return commonDivisor;
}

long longFromDouble(double f) {
    double diff = fabs(f - (double)((long)f));
    if (diff >= 0.5) {
        if (f >= 0)
            return (long)f+1;
        else
            return (long)f-1;
    }
    else
        return (long)f;
}
