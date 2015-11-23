//
//  RationalNumber.cpp
//  MathTools
//
//  Created by Richard Chien on 4/22/13.
//
//

#include "RationalNumber.h"

using namespace std;

#pragma mark - Convert Methods

RationalNumber fractionFromDouble(double lf) {
    double nume = lf;
    long deno = 1;
    
    while (!isInt(nume)) {
        nume *= 10;
        deno *= 10;
    }
    
    RationalNumber result(longFromDouble(nume), deno);
    result.reduce();
    return result;
}

RationalNumber frac(double lf) {
    return fractionFromDouble(lf);
}

#pragma mark - Transform Methods

void RationalNumber::reduce() {
    long commonDiv = commonDivisorOf(numerator, denominator);
    
    numerator /= commonDiv;
    denominator /= commonDiv;
    
    if (denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
}

void simplifyFracs(RationalNumber &a, RationalNumber &b) {
    a.reduce();
    b.reduce();
    
    if (a == 0 && b != 0)
        b = 1;
    else if (a != 0 && b == 0)
        a = 1;
    else {
        long commonMulti = commonMultipleOf(a.denominator, b.denominator);
        a *= commonMulti;
        b *= commonMulti;
        
        long commonDivisor = commonDivisorOf(a.numerator, b.numerator);
        a /= commonDivisor;
        b /= commonDivisor;
    }
}

void simplifyFracs(RationalNumber &a, RationalNumber &b, RationalNumber &c) {
    a.reduce();
    b.reduce();
    c.reduce();
    
    if (a == 0 && (b != 0 || c != 0))
        simplifyFracs(b, c);
    else if (b == 0 && (a != 0 || c != 0))
        simplifyFracs(a, c);
    else if (c == 0 && (a != 0 || b != 0))
        simplifyFracs(a, b);
    else {
        long commonMulti = commonMultipleOf(a.denominator, b.denominator, c.denominator);
        a *= commonMulti;
        b *= commonMulti;
        c *= commonMulti;
        
        long commonDivisor = commonDivisorOf(a.numerator, b.numerator, c.numerator);
        a /= commonDivisor;
        b /= commonDivisor;
        c /= commonDivisor;
    }
}

#pragma mark - Caculate Methods

RationalNumber RationalNumber::add(RationalNumber f) {
    // a/b + c/d = ((a*d) + (b*c)) / (b*d)
    
    this->reduce();
    f.reduce();
    
    RationalNumber result;
    
    long d = commonMultipleOf(denominator, f.denominator);
    result.denominator = d;
    result.numerator = numerator * (d / denominator) + f.numerator * (d / f.denominator);
    
    result.reduce();
    return result;
}

RationalNumber RationalNumber::subtract(RationalNumber f) {
    // a/b - c/d = a/b - c/d = a/b + (-c/d)
    
    return this->add(f.changeSign());
}

RationalNumber RationalNumber::multiply(RationalNumber f) {
    // a/b * c/d = a*c / b*d
    
    this->reduce();
    f.reduce();
    
    RationalNumber num1(numerator, f.denominator), num2(f.numerator, denominator);
    num1.reduce();
    num2.reduce();
    
    RationalNumber result;
    
    result.numerator = num1.numerator * num2.numerator;
    result.denominator = num1.denominator * num2.denominator;
    
    result.reduce();
    return result;
}

RationalNumber RationalNumber::divide(RationalNumber f) {
    // a/b / c/d = a/b * d/c
    
    return this->multiply(f.invert());
}

RationalNumber RationalNumber::invert() {
    RationalNumber result(denominator, numerator);
    result.reduce();
    return result;
}

RationalNumber RationalNumber::changeSign() {
    RationalNumber result;
    
    result.numerator = -numerator;
    result.denominator = denominator;
    
    result.reduce();
    return result;
}

RationalNumber RationalNumber::xSquared() {
    this->reduce();
    RationalNumber result(numerator * numerator, denominator * denominator);
    return result;
}

#pragma mark - Caculate Operators

RationalNumber RationalNumber::operator = (const double &lf) {
    *this = fractionFromDouble(lf);
    return *this;
}

RationalNumber RationalNumber::operator + (const RationalNumber &frac) {
    return this->add(frac);
}

RationalNumber RationalNumber::operator + (const double &lf) {
    RationalNumber frac = fractionFromDouble(lf);
    return *this + frac;
}

RationalNumber RationalNumber::operator += (const RationalNumber &frac) {
    *this = *this + frac;
    return *this;
}

RationalNumber RationalNumber::operator += (const double &lf) {
    *this = *this + lf;
    return *this;
}

RationalNumber RationalNumber::operator - (const RationalNumber &frac) {
    return this->subtract(frac);
}

RationalNumber RationalNumber::operator - (const double &lf) {
    RationalNumber frac = fractionFromDouble(lf);
    return *this - frac;
}

RationalNumber RationalNumber::operator -= (const RationalNumber &frac) {
    *this = *this - frac;
    return *this;
}

RationalNumber RationalNumber::operator -= (const double &lf) {
    *this = *this - lf;
    return *this;
}

RationalNumber RationalNumber::operator * (const RationalNumber &frac) {
    return this->multiply(frac);
}

RationalNumber RationalNumber::operator * (const double &lf) {
    RationalNumber frac = fractionFromDouble(lf);
    return *this * frac;
}

RationalNumber RationalNumber::operator *= (const RationalNumber &frac) {
    *this = *this * frac;
    return *this;
}

RationalNumber RationalNumber::operator *= (const double &lf) {
    *this = *this * lf;
    return *this;
}

RationalNumber RationalNumber::operator / (const RationalNumber &frac) {
    return this->divide(frac);
}

RationalNumber RationalNumber::operator / (const double &lf) {
    RationalNumber frac = fractionFromDouble(lf);
    return *this / frac;
}

RationalNumber RationalNumber::operator /= (const RationalNumber &frac) {
    *this = *this / frac;
    return *this;
}

RationalNumber RationalNumber::operator /= (const double &lf) {
    *this = *this / lf;
    return *this;
}

#pragma mark - Compare Operators

bool RationalNumber::operator == (const RationalNumber &frac) {
    return (*this - frac).doubleValue() == 0;
}

bool RationalNumber::operator == (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this == param;
}

bool RationalNumber::operator != (const RationalNumber &frac) {
    return (*this - frac).doubleValue() != 0;
}

bool RationalNumber::operator != (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this != param;
}

bool RationalNumber::operator > (const RationalNumber &frac) {
    return (*this - frac).doubleValue() > 0;
}

bool RationalNumber::operator > (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this > param;
}

bool RationalNumber::operator >= (const RationalNumber &frac) {
    return (*this - frac).doubleValue() >= 0;
}

bool RationalNumber::operator >= (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this >= param;
}

bool RationalNumber::operator < (const RationalNumber &frac) {
    return (*this - frac).doubleValue() < 0;
}

bool RationalNumber::operator < (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this < param;
}

bool RationalNumber::operator <= (const RationalNumber &frac) {
    return (*this - frac).doubleValue() <= 0;
}

bool RationalNumber::operator <= (const double &lf) {
    RationalNumber param = fractionFromDouble(lf);
    return *this <= param;
}

#pragma mark - I/O Operators

ostream & operator << (ostream &out, const RationalNumber &frac) {
    out << frac.stringValue();
    return out;
}

#pragma mark - Set and Get Methods

void RationalNumber::setFraction(long n, long d) {
    numerator = n;
    denominator = d;
    this->reduce();
}

double RationalNumber::doubleValue() const {
    return (double)numerator / denominator;
}

string RationalNumber::stringValue() const {
    RationalNumber self = *this;
    self.reduce();
    long n = self.numerator;
    long d = self.denominator;
    
    stringstream ss;
    
    if (d == 1) ss << n;
    else ss << n << '/' << d;
    
    string result = ss.str();
    return result;
}

string RationalNumber::stringLatexValue() const {
    RationalNumber self = *this;
    self.reduce();
    long n = self.numerator;
    long d = self.denominator;
    
    stringstream ss;
    
    if (d == 1) ss << n;
    else ss << (n < 0 ? "-" : "") << "\\frac{" << fabs(n) << "}{" << d << "}";
    
    string result = ss.str();
    return result;
}
