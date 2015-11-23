//
//  Equation.c
//  MathTools
//
//  Created by Richard Chien on 5/12/13.
//
//

#include "Equation.h"

// These functions here will not do validation check

#pragma mark - One Unknown

LineEquaRt rootOfLinearEquation(const LineEquaParam &param) {
    // ax + b = c
    RationalNumber a = param.a, b = param.b, c = param.c;
    LineEquaRt result;
    
    result.x = (c - b) / a;
    
    return result;
}

QuadEquaRt rootOfQuadraticEquation(const QuadEquaParam &param) {
    // ax^2 + bx + c = 0
    RationalNumber a = param.a, b = param.b, c = param.c;
    QuadEquaRt result;
    RationalNumber delta, p;
    QuadraticIrrational q;
    
    // According to the mathematical formula
    delta = b * b - a * c * 4;
    if (delta >= 0) {
        p = b.changeSign() / (a * 2);
        q = sqrt(delta) / (a * 2);
        
        result.x1 = q.changeSign() + p;
        result.x2 = q + p;
    }
    // If delta < 0, the equation has no real roots
    else {
        result.hasRealRoots = false;
    }
    
    return result;
}

CubicEquaRt rootOfCubicEquation(const CubicEquaParam &param) {
    // ax^3 + bx^2 + cx + d = 0
    double a = param.a.doubleValue(), b = param.b.doubleValue(), c = param.c.doubleValue(), d = param.d.doubleValue();
    CubicEquaRt result;
    
    double A, B, C, delta;
    
    // According to the mathematical formula
    A = b * b - 3 * a * c;
    B = b * c - 9 * a * d;
    C = c * c - 3 * b * d;
    delta = B * B - 4 * A * C;
    
    // Situation 0
    // ax^3 = 0, absolutely x = 0
    if (b == 0 && c == 0 && d == 0) {
        result.x1 = result.x2 = result.x3 = {0, 0};
    }
    // Situation I
    else if (A == B && B == 0) {
        ComplexNumber x;
        x.real = -c / b;
        x.imaginary = 0;
        result.x1 = result.x2 = result.x3 = x;
    }
    // Situation II
    else if (delta > 0) {
        double Y1, Y2;
        Y1 = A * b + 1.5 * a * (-B + sqrt(delta));
        Y2 = A * b + 1.5 * a * (-B - sqrt(delta));
        
        ComplexNumber x1, x2, x3;
        x1.real = (-b - (cbrt(Y1) + cbrt(Y2))) / (3 * a);
        x1.imaginary = 0;
        x2.real = x3.real = (-b + 0.5 * (cbrt(Y1) + cbrt(Y2))) / (3 * a);
        x2.imaginary = ((sqrt(3) / 2) * (cbrt(Y1) - cbrt(Y2))) / (3 * a);
        x3.imaginary = (-(sqrt(3) / 2) * (cbrt(Y1) - cbrt(Y2))) / (3 * a);
        result.x1 = x1;
        result.x2 = x2;
        result.x3 = x3;
    }
    // Situation III
    else if (delta == 0) {
        double K;
        K = B / A;
        
        ComplexNumber x1, x23;
        x1.real = -b / a + K;
        x1.imaginary = 0;
        x23.real = -K / 2;
        x23.imaginary = 0;
        result.x1 = x1;
        result.x2 = result.x3 = x23;
    }
    // Situation IV
    // delta < 0
    else {
        double T, thita;
        T = (2 * A * b - 3 * a * B) / (2 * sqrt(pow(A, 3)));
        thita = acos(T);
        
        ComplexNumber x1, x2, x3;
        x1.real = (-b - 2 * sqrt(A) * cos(thita / 3)) / (3 * a);
        x1.imaginary = 0;
        x2.real = (-b + sqrt(A) * (cos(thita / 3) + sqrt(3) * sin(thita / 3))) / (3 * a);
        x2.imaginary = 0;
        x3.real = (-b + sqrt(A) * (cos(thita / 3) - sqrt(3) * sin(thita / 3))) / (3 * a);
        x3.imaginary = 0;
        result.x1 = x1;
        result.x2 = x2;
        result.x3 = x3;
    }
    
    return result;
}

#pragma mark - Multiple Unknowns

TwoUnknEquaRt rootOfTwoUnknownsEquation(const TwoUnknEquaParam &param) {
    // a1x + b1y = c1, a2x + b2y = c2
    RationalNumber a1 = param.a1, b1 = param.b1, c1 = param.c1;
    RationalNumber a2 = param.a2, b2 = param.b2, c2 = param.c2;
    TwoUnknEquaRt result;
    
    // Cramer's Law
    RationalNumber det, detx, dety;
    det = a1 * b2 - a2 * b1;
    detx = c1 * b2 - c2 * b1;
    dety = a1 * c2 - a2 * c1;
    
    result.x = detx / det;
    result.y = dety / det;
    
    return result;
}

ThreeUnknEquaRt rootOfThreeUnknownsEquation(const ThreeUnknEquaParam &param) {
    // a1x + b1y + c1z = d1, a2x + b2y + c2z = d2, a3x + b3y + c3z = d3
    RationalNumber a1 = param.a1, b1 = param.b1, c1 = param.c1, d1 = param.d1;
    RationalNumber a2 = param.a2, b2 = param.b2, c2 = param.c2, d2 = param.d2;
    RationalNumber a3 = param.a3, b3 = param.b3, c3 = param.c3, d3 = param.d3;
    ThreeUnknEquaRt result;
    
    // Cramer's Law
    RationalNumber det, detx, dety, detz;
    det = a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1);
    detx = d1 * (b2 * c3 - b3 * c2) + d2 * (b3 * c1 - b1 * c3) + d3 * (b1 * c2 - b2 * c1);
    dety = a1 * (d2 * c3 - d3 * c2) + a2 * (d3 * c1 - d1 * c3) + a3 * (d1 * c2 - d2 * c1);
    detz = a1 * (b2 * d3 - b3 * d2) + a2 * (b3 * d1 - b1 * d3) + a3 * (b1 * d2 - b2 * d1);
    
    result.x = detx / det;
    result.y = dety / det;
    result.z = detz / det;
    
    return result;
}
