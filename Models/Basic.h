//
//  Basic.h
//  MathTools
//
//  Created by Richard Chien on 6/29/15.
//
//

#ifndef __MathTools__Basic__
#define __MathTools__Basic__

#include <cmath>
#include <vector>

// Basic math functions
bool isInt(double a);
long commonDivisorOf(long a, long b);
long commonMultipleOf(long a, long b);
long commonDivisorOf(long a, long b, long c);
long commonMultipleOf(long a, long b, long c);
long commonDivisorOf(std::vector<long> nums);
long longFromDouble(double f); // round-off

#endif
