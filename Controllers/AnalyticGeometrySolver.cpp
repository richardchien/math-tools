//
//  AnalyticGeometrySolver.cpp
//  MathTools
//
//  Created by Richard Chien on 7/13/15.
//
//

#include "AnalyticGeometrySolver.h"

using namespace std;

#pragma mark - Solve to Get Expression

SolvingResult solveLineWithTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) Q(x2, y2) Ax + By + C = 0
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        RCPoint Q{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3])};
        
        if (P.x == Q.x && P.y == Q.y) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            Line line = lineWithTwoPoints(P, Q);
            stringstream ss;
            
            if (line.A != 0)
                ss << (line.A == 1 ? "" : (latex ? line.A.stringLatexValue() : line.A.stringValue())) << "x";
            if (line.B != 0)
                ss << (line.B > 0 ? "+" : "") << (line.B == 1 ? "" : (latex ? line.B.stringLatexValue() : line.B.stringValue())) << "y";
            if (line.C != 0)
                ss << (line.C > 0 ? "+" : "") << (latex ? line.C.stringLatexValue() : line.C.stringValue());
            ss << "=0.";
            
            string str = ss.str();
            if (str[0] == '+')
                str = str.substr(1, str.size()-1);
            
            outputStr = str;
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveCircleWithThreePoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) Q(x2, y2) M(x3, y3) x^2 + y^2 + Dx + Ey + F = 0
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        RCPoint Q{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3])};
        RCPoint M{fractionFromString(inputStrs[4]), fractionFromString(inputStrs[5])};
        
        Line linePQ = lineWithTwoPoints(P, Q);
        if (pointIsOnLine(M, linePQ)) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            Circle circle = circleWithThreePoints(P, Q, M);
            stringstream ss;
            
            ss << "x^2+y^2";
            if (circle.D != 0)
                ss << (circle.D > 0 ? "+" : "") << (circle.D == 1 ? "" : (latex ? circle.D.stringLatexValue() : circle.D.stringValue())) << "x";
            if (circle.E != 0)
                ss << (circle.E > 0 ? "+" : "") << (circle.E == 1 ? "" : (latex ? circle.E.stringLatexValue() : circle.E.stringValue())) << "y";
            if (circle.F != 0)
                ss << (circle.F > 0 ? "+" : "") << (latex ? circle.F.stringLatexValue() : circle.F.stringValue());
            ss << "=0.";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveEllipseWithTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) Q(x2, y2) mx^2 + ny^2 = 1
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        RCPoint Q{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3])};
        
        RationalNumber det = P.x.xSquared() * Q.y.xSquared() - Q.x.xSquared() * P.y.xSquared();
        if (det == 0) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            Ellipse ellipse = ellipseWithTwoPoints(P, Q);
            stringstream ss;
            
            if (ellipse.m == 0 || ellipse.n == 0) {
                return SolvingResultErrorCannotSolve;
            }
            
            ss << (ellipse.m == 1 ? "" : (latex ? ellipse.m.stringLatexValue() : ellipse.m.stringValue())) << "x^2";
            ss << (ellipse.n > 0 ? "+" : "") << (ellipse.n == 1 ? "" : (latex ? ellipse.n.stringLatexValue() : ellipse.n.stringValue())) << "y^2";
            ss << "=1.";
            
            string str = ss.str();
            if (str[0] == '+')
                str = str.substr(1, str.size()-1);
            
            outputStr = str;
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveQuadraticFunctionWithThreePoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) Q(x2, y2) M(x3, y3) y = ax^2 + bx + c
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        RCPoint Q{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3])};
        RCPoint M{fractionFromString(inputStrs[4]), fractionFromString(inputStrs[5])};
        
        Line linePQ = lineWithTwoPoints(P, Q);
        if (pointIsOnLine(M, linePQ)) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            QuadraticFunction qfunc = quadraticFunctionWithThreePoints(P, Q, M);
            stringstream ss;
            
            ss << "y=";
            // Excluded the situation where a = 0 above, so no need to check it
            ss << (qfunc.a == 1 ? "" : (latex ? qfunc.a.stringLatexValue() : qfunc.a.stringValue())) << "x^2";
            if (qfunc.b != 0)
                ss << (qfunc.b > 0 ? "+" : "") << (qfunc.b == 1 ? "" : (latex ? qfunc.b.stringLatexValue() : qfunc.b.stringValue())) << "x";
            if (qfunc.c != 0)
                ss << (qfunc.c > 0 ? "+" : "") << (qfunc.c == 1 ? "" : (latex ? qfunc.c.stringLatexValue() : qfunc.c.stringValue()));
            
            ss << ".";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}

#pragma mark - Solve to Get Distance
SolvingResult solveDistanceBetweenTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) Q(x2, y2)
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        RCPoint Q{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3])};
        
        QuadraticIrrational dist = distanceBetweenTwoPoints(P, Q);
        stringstream ss;
        
        ss << "d=" << (latex ? dist.stringLatexValue() : dist.stringValue());
        if (!isInt(dist.doubleValue())) {
            ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << dist.doubleValue();
        }
        ss << ".";
        
        outputStr = ss.str();
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveDistanceBetweenPointAndLine(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // P(x1, y1) L: Ax + By + C = 0
        RCPoint P{fractionFromString(inputStrs[0]), fractionFromString(inputStrs[1])};
        Line line{fractionFromString(inputStrs[2]), fractionFromString(inputStrs[3]), fractionFromString(inputStrs[4])};
        
        if (line.A == 0 && line.B == 0) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            QuadraticIrrational dist = distanceBetweenPointAndLine(P, line);
            stringstream ss;
            
            ss << "d=" << (latex ? dist.stringLatexValue() : dist.stringValue());
            if (!isInt(dist.doubleValue())) {
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << dist.doubleValue();
            }
            ss << ".";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}
