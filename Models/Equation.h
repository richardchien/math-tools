//
//  Equation.h
//  MathTools
//
//  Created by Richard Chien on 5/12/13.
//
//

#ifndef __MathTools__Equation__
#define __MathTools__Equation__

#include <iostream>
#include <cmath>

#include "ComplexNumber.h"
#include "QuadraticIrrational.h"

struct LinearEquationParameters {
    // ax + b = c
    RationalNumber a, b, c;
};

struct LinearEquationRoots {
    RationalNumber x;
};

struct QuadraticEquationParameters {
    // ax^2 + bx + c = 0
    RationalNumber a, b, c;
};

struct QuadraticEquationRoots {
    QuadraticIrrational x1, x2;
    bool hasRealRoots = true;
};

struct CubicEquationParameters {
    // ax^3 + bx^2 + cx + d = 0
    RationalNumber a, b, c, d;
};

struct CubicEquationRoots {
    ComplexNumber x1, x2, x3;
};

struct TwoUnknownsEquationParameters {
    // a1x + b1y = c1
    // a2x + b2y = c2
    RationalNumber a1, b1, c1;
    RationalNumber a2, b2, c2;
};

struct TwoUnknownsEquationRoots {
    RationalNumber x, y;
};

struct ThreeUnknownsEquationParameters {
    // a1x + b1y + c1z = d1
    // a2x + b2y + c2z = d2
    // a3x + b3y + c3z = d3
    RationalNumber a1, b1, c1, d1;
    RationalNumber a2, b2, c2, d2;
    RationalNumber a3, b3, c3, d3;
};

struct ThreeUnknownsEquationRoots {
    RationalNumber x, y, z;
};

using LineEquaParam = LinearEquationParameters;
using LineEquaRt = LinearEquationRoots;
using QuadEquaParam = QuadraticEquationParameters;
using QuadEquaRt = QuadraticEquationRoots;
using CubicEquaParam = CubicEquationParameters;
using CubicEquaRt = CubicEquationRoots;
using TwoUnknEquaParam = TwoUnknownsEquationParameters;
using TwoUnknEquaRt = TwoUnknownsEquationRoots;
using ThreeUnknEquaParam = ThreeUnknownsEquationParameters;
using ThreeUnknEquaRt = ThreeUnknownsEquationRoots;

// These functions here will not do validation check
LineEquaRt rootOfLinearEquation(const LineEquaParam &param);
QuadEquaRt rootOfQuadraticEquation(const QuadEquaParam &param);
CubicEquaRt rootOfCubicEquation(const CubicEquaParam &param);
TwoUnknEquaRt rootOfTwoUnknownsEquation(const TwoUnknEquaParam &param);
ThreeUnknEquaRt rootOfThreeUnknownsEquation(const ThreeUnknEquaParam &param);

#endif
