//
//  RationalNumber.h
//  MathTools
//
//  Created by Richard Chien on 4/22/13.
//
//

#ifndef __MathTools__RationalNumber__
#define __MathTools__RationalNumber__

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "Basic.h"

class RationalNumber {
public:
    // frac = numerator / denominator
    long numerator;
    long denominator;
public:
    RationalNumber(long n = 0, long d = 1)
    : numerator(n), denominator(d) { this->reduce(); };
    RationalNumber(RationalNumber n, RationalNumber d) { *this = n / d; };
    ~RationalNumber() {};
    
    // Caculate Methods
    RationalNumber add(RationalNumber f);
    RationalNumber subtract(RationalNumber f);
    RationalNumber multiply(RationalNumber f);
    RationalNumber divide(RationalNumber f);
    RationalNumber invert();
    RationalNumber changeSign();
    RationalNumber xSquared();
    
    // Caculate Operators
    RationalNumber operator = (const double &lf);
    RationalNumber operator + (const RationalNumber &frac);
    RationalNumber operator + (const double &lf);
    RationalNumber operator += (const RationalNumber &frac);
    RationalNumber operator += (const double &lf);
    RationalNumber operator - (const RationalNumber &frac);
    RationalNumber operator - (const double &lf);
    RationalNumber operator -= (const RationalNumber &frac);
    RationalNumber operator -= (const double &lf);
    RationalNumber operator * (const RationalNumber &frac);
    RationalNumber operator * (const double &lf);
    RationalNumber operator *= (const RationalNumber &frac);
    RationalNumber operator *= (const double &lf);
    RationalNumber operator / (const RationalNumber &frac);
    RationalNumber operator / (const double &lf);
    RationalNumber operator /= (const RationalNumber &frac);
    RationalNumber operator /= (const double &lf);
    
    // Compare Operators
    bool operator == (const RationalNumber &frac);
    bool operator == (const double &lf);
    bool operator != (const RationalNumber &frac);
    bool operator != (const double &lf);
    bool operator > (const RationalNumber &frac);
    bool operator > (const double &lf);
    bool operator >= (const RationalNumber &frac);
    bool operator >= (const double &lf);
    bool operator < (const RationalNumber &frac);
    bool operator < (const double &lf);
    bool operator <= (const RationalNumber &frac);
    bool operator <= (const double &lf);
    
    // I/O Operators
    friend std::ostream & operator << (std::ostream &out, const RationalNumber &frac);
    friend std::istream & operator >> (std::istream &in, const RationalNumber &frac);
    
    // Set and Get Methods
    void setFraction(long n, long d);
    double doubleValue() const;
    std::string stringValue() const;
    std::string stringLatexValue() const;
    
    // Transform Methods
    void reduce();
};

// Convert Methods
RationalNumber fractionFromDouble(double lf);
RationalNumber frac(double lf);

// Transform Methods
//// Something like transform 2/3 and 4/5 to 10 and 12 (directly manipulate on origin fraction)
void simplifyFracs(RationalNumber &a, RationalNumber &b);
void simplifyFracs(RationalNumber &a, RationalNumber &b, RationalNumber &c);

#endif
