//
//  AnalyticGeometry.h
//  MathTools
//
//  Created by Richard Chien on 1/30/14.
//
//

#ifndef __MathTools__AnalyticGeometry__
#define __MathTools__AnalyticGeometry__

#include "RationalNumber.h"
#include "QuadraticIrrational.h"
#include "Equation.h"

struct RCPoint {
    RationalNumber x, y;
    
};

struct Line {
    // Ax + By + C = 0
    RationalNumber A, B, C;
};

struct Circle {
    // x^2 + y^2 + Dx + Ey + F = 0
    RationalNumber D, E, F;
};

struct Ellipse {
    // mx^2 + ny^2 = 1
    RationalNumber m, n;
};

struct QuadraticFunction {
    // y = ax^2 + bx + c
    RationalNumber a, b, c;
};

// Check Methods
bool pointIsOnLine(RCPoint P, Line L);
bool pointIsOnCircle(RCPoint P, Circle C);
bool pointIsOnEllipse(RCPoint P, Ellipse E);
bool pointIsOnQuadraticFunction(RCPoint P, QuadraticFunction QF);

// Calculate Methods
//// Get Expression
Line lineWithTwoPoints(RCPoint P, RCPoint Q);
Circle circleWithThreePoints(RCPoint P, RCPoint Q, RCPoint M);
Ellipse ellipseWithTwoPoints(RCPoint P, RCPoint Q);
QuadraticFunction quadraticFunctionWithThreePoints(RCPoint P, RCPoint Q, RCPoint M);
//// Get Distance
QuadraticIrrational distanceBetweenTwoPoints(RCPoint P, RCPoint Q);
QuadraticIrrational distanceBetweenPointAndLine(RCPoint P, Line L);

#endif
