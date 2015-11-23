//
//  ComplexNumber.cpp
//  MathTools
//
//  Created by Richard Chien on 7/17/15.
//
//

#include "ComplexNumber.h"

using namespace std;

string ComplexNumber::stringValue() const {
    double real = this->real;
    double imag = this->imaginary;
    stringstream ss;
    
    if (fabs(real - 0) <= 0.00000001) {
        if (fabs(imag - 0) <= 0.00000001)
            ss << "0";
        else
            ss << imag << "i";
    }
    else {
        if (fabs(imag - 0) <= 0.00000001)
            ss << real;
        else
            ss << real << (imag < 0 ? "" : "+") << imag << "i";
    }
    
    return ss.str();
}

string ComplexNumber::stringLatexValue() const {
    return this->stringValue();
}
