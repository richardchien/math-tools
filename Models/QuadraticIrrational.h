//
//  QuadraticIrrational.h
//  MathTools
//
//  Created by Richard Chien on 11/19/13.
//
//

#ifndef __MathTools__QuadraticIrrational__
#define __MathTools__QuadraticIrrational__

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "RationalNumber.h"

class QuadraticIrrational {

public:
    // qi = coefficient * √radicand + ratio
    RationalNumber coefficient;
    RationalNumber radicand;
    RationalNumber ratio;
public:
    QuadraticIrrational(RationalNumber c = 1, RationalNumber rad = 0, RationalNumber rat = 0)
    : coefficient(c), radicand(rad), ratio(rat) { this->simplify(); };
    ~QuadraticIrrational() {};
    
    // Calculate Methods
    QuadraticIrrational add(RationalNumber f);
    QuadraticIrrational subtract(RationalNumber f);
    QuadraticIrrational multiply(RationalNumber f);
    QuadraticIrrational divide(RationalNumber f);
    QuadraticIrrational changeSign();
    
    // Calculate Operators
    QuadraticIrrational operator = (const RationalNumber &frac);
    QuadraticIrrational operator = (const double &lf);
    QuadraticIrrational operator + (const RationalNumber &frac);
    QuadraticIrrational operator + (const double &lf);
    QuadraticIrrational operator += (const RationalNumber &frac);
    QuadraticIrrational operator += (const double &lf);
    QuadraticIrrational operator - (const RationalNumber &frac);
    QuadraticIrrational operator - (const double &lf);
    QuadraticIrrational operator -= (const RationalNumber &frac);
    QuadraticIrrational operator -= (const double &lf);
    QuadraticIrrational operator * (const RationalNumber &frac);
    QuadraticIrrational operator * (const double &lf);
    QuadraticIrrational operator *= (const RationalNumber &frac);
    QuadraticIrrational operator *= (const double &lf);
    QuadraticIrrational operator / (const RationalNumber &frac);
    QuadraticIrrational operator / (const double &lf);
    QuadraticIrrational operator /= (const RationalNumber &frac);
    QuadraticIrrational operator /= (const double &lf);
    
    // I/O Operators
    friend std::ostream & operator << (std::ostream &out, const QuadraticIrrational &qi);
    
    // Transform Methods
    void simplify();
    
    // Set and Get Methods
    double doubleValue() const;
    std::string stringValue() const;
    std::string stringLatexValue() const;
};

QuadraticIrrational sqrt(const RationalNumber& frac);

#endif
