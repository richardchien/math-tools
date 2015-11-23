//
//  AnalyticGeometry.cpp
//  MathTools
//
//  Created by Richard Chien on 7/13/15.
//
//

#include "AnalyticGeometry.h"

#pragma mark - Check Methods

bool pointIsOnLine(RCPoint P, Line L) {
    if (L.A * P.x + L.B * P.y + L.C == 0)
        return true;
    else
        return false;
}

bool pointIsOnCircle(RCPoint P, Circle C) {
    if (P.x.xSquared() + P.y.xSquared() + C.D * P.x + C.E * P.y + C.F == 0)
        return true;
    else
        return false;
}

bool pointIsOnEllipse(RCPoint P, Ellipse E) {
    if (E.m * P.x.xSquared() + E.n * P.y.xSquared() == 1)
        return true;
    else
        return false;
}

bool pointIsOnQuadraticFunction(RCPoint P, QuadraticFunction QF) {
    if (P.y == QF.a * P.x.xSquared() + QF.b * P.x + QF.c)
        return true;
    else
        return false;
}

#pragma mark - Calculate Methods

//  These functions here will not do validation check

#pragma mark --- Get Expression

Line lineWithTwoPoints(RCPoint P, RCPoint Q) {
    Line result;
    
    // Formula is abtained from y-y0=k(x-x0)
    result.A = P.y - Q.y;
    result.B = Q.x - P.x;
    result.C = P.y * (P.x - Q.x) - P.x * (P.y - Q.y);
    simplifyFracs(result.A, result.B, result.C);
    
//    if (result.C == 0) {
//        if (result.B == 0)
//            result.A = 1;
//        else if (result.A == 0)
//            result.B = 1;
//    }
    
    return result;
}

Circle circleWithThreePoints(RCPoint P, RCPoint Q, RCPoint M) {
    Circle result;
    
    ThreeUnknEquaRt root = rootOfThreeUnknownsEquation({P.x, P.y, frac(1), (P.x.xSquared() + P.y.xSquared()).changeSign(),
        Q.x, Q.y, frac(1), (Q.x.xSquared() + Q.y.xSquared()).changeSign(),
        M.x, M.y, frac(1), (M.x.xSquared() + M.y.xSquared()).changeSign()});
    result.D = root.x;
    result.E = root.y;
    result.F = root.z;
    //simplifyFracs(result.D, result.E, result.F);
    // Because in x^2+y^2+Dx+Ey+F=0, the coefficent of x^2 is 1, can't simplify D, E, F here
    
    return result;
}

Ellipse ellipseWithTwoPoints(RCPoint P, RCPoint Q) {
    Ellipse result;
    
    TwoUnknEquaRt root = rootOfTwoUnknownsEquation({P.x.xSquared(), P.y.xSquared(), frac(1),
        Q.x.xSquared(), Q.y.xSquared(), frac(1)});
    result.m = root.x;
    result.n = root.y;
    //simplifyFracs(result.m, result.n);
    // mx^2+ny^2=1, can't simplify here, like the function above
    
    return result;
}

QuadraticFunction quadraticFunctionWithThreePoints(RCPoint P, RCPoint Q, RCPoint M) {
    QuadraticFunction result;
    
    ThreeUnknEquaRt root = rootOfThreeUnknownsEquation({P.x.xSquared(), P.x, frac(1), P.y,
        Q.x.xSquared(), Q.x, frac(1), Q.y,
        M.x.xSquared(), M.x, frac(1), M.y});
    result.a = root.x;
    result.b = root.y;
    result.c = root.z;
    //simplifyFracs(result.a, result.b, result.c);
    // y=ax^2+bx+c can't simplify here, like the function above
    
    return result;
}

#pragma mark --- Get Distance

QuadraticIrrational distanceBetweenTwoPoints(RCPoint P, RCPoint Q) {
    QuadraticIrrational result;

    // d = √((x1-x2)^2 + (y1-y2)^2)
    RationalNumber frac = (P.x - Q.x).xSquared() + (P.y - Q.y).xSquared();
    result = sqrt(frac);

    return result;
}

QuadraticIrrational distanceBetweenPointAndLine(RCPoint P, Line L) {
    QuadraticIrrational result;
    
    // d = |Ax0+By0+C| * √(1/(A^2+B^2))
    RationalNumber num1 = L.A * P.x + L.B * P.y + L.C;
    num1 = num1 > 0 ? num1 : num1.changeSign();
    RationalNumber num2UnderRoot = (L.A.xSquared() + L.B.xSquared()).invert();
    QuadraticIrrational num2 = sqrt(num2UnderRoot);
    result = num2 * num1;
    
    return result;
}
