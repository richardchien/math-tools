//
//  ComplexNumber.h
//  MathTools
//
//  Created by Richard Chien on 7/9/13.
//
//

#ifndef __MathTools__ComplexNumber__
#define __MathTools__ComplexNumber__

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class ComplexNumber {
public:
    double real, imaginary;
public:
    std::string stringValue() const;
    std::string stringLatexValue() const;
};

#endif
