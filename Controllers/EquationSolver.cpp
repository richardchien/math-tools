//
//  EquationSolver.cpp
//  MathTools
//
//  Created by Richard Chien on 7/13/15.
//
//

#include "EquationSolver.h"

using namespace std;

#pragma mark - One Unknown

SolvingResult solveLinearEquation(vector<string> &inputStrs, string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // ax + b = c
        RationalNumber a = fractionFromString(inputStrs[0]);
        RationalNumber b = fractionFromString(inputStrs[1]);
        RationalNumber c = fractionFromString(inputStrs[2]);
        
        if (a == 0) {
            outputStr = b == c ? "x可为任何实数(x∈R)." : "x无解(x∈∅).";
        }
        else {
            LineEquaParam params{a, b, c};
            LineEquaRt root = rootOfLinearEquation(params);
            stringstream ss;
            ss << "x=" << (latex ? root.x.stringLatexValue() : root.x.stringValue());
            if (!isInt(root.x.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << root.x.doubleValue();
            }
            ss << ".";
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveQuadraticEquation(vector<string> &inputStrs, string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // ax^2 + bx + c = 0;
        RationalNumber a = fractionFromString(inputStrs[0]);
        RationalNumber b = fractionFromString(inputStrs[1]);
        RationalNumber c = fractionFromString(inputStrs[2]);
        
        if (a == 0) {
            // a = 0, solve as linear equation
            vector<string> in{b.stringValue(), c.stringValue(), "0"};
            solveLinearEquation(in, outputStr, latex);
        }
        else {
            RationalNumber delta = b * b - a * c * 4;
            if (delta < 0) {
                outputStr = "x无实数解.";
            }
            else {
                QuadEquaParam params{a, b, c};
                QuadEquaRt roots = rootOfQuadraticEquation(params);
                stringstream ss;
                
                if (delta == 0) {
                    // x1 = x2, show in one line
                    if (latex)
                        ss << "x_1=x_2=" << roots.x1.stringLatexValue();
                    else
                        ss << "x1=x2=" << roots.x1.stringValue();
                    if (!isInt(roots.x1.doubleValue())) {
                        //ss << (latex ? "\\\\" : "\n");
                        ss <<"≈" << setiosflags(ios::fixed) << setprecision(6) << roots.x1.doubleValue();
                    }
                    
                    ss << ".";
                }
                else {
                    // output prefix
                    if (latex)
                        ss << "\\begin{align*}";
                    
                    // output x1
                    if (latex)
                        ss << "&" << "x_1=" << roots.x1.stringLatexValue();
                    else
                        ss << "x1=" << roots.x1.stringValue();
                    
                    if (!isInt(roots.x1.doubleValue())) {
                        //ss << (latex ? "\\\\" : "\n");
                        ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.x1.doubleValue();
                    }
                    
                    ss << "," << (latex ? "\\\\" : "\n");
                    
                    // output x2
                    if (latex)
                        ss << "&" << "x_2=" << roots.x2.stringLatexValue();
                    else
                        ss << "x2=" << roots.x2.stringValue();
                    
                    if (!isInt(roots.x2.doubleValue())) {
                        //ss << (latex ? "\\\\" : "\n");
                        ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.x2.doubleValue();
                    }
                    
                    ss << ".";
                    
                    // output suffix
                    if (latex)
                        ss << "\\end{align*}";
                }
                
                outputStr = ss.str();
            }
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveCubicEquation(vector<string> &inputStrs, string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // ax^3 + bx^2 + cx + d = 0;
        RationalNumber a = fractionFromString(inputStrs[0]);
        RationalNumber b = fractionFromString(inputStrs[1]);
        RationalNumber c = fractionFromString(inputStrs[2]);
        RationalNumber d = fractionFromString(inputStrs[3]);
        
        if (a == 0) {
            // a = 0, solve as quadratic equation
            vector<string> in{b.stringValue(), c.stringValue(), d.stringValue()};
            solveQuadraticEquation(in, outputStr, latex);
        }
        else {
            CubicEquaParam params{a, b, c, d};
            CubicEquaRt roots = rootOfCubicEquation(params);
            stringstream ss;
            
            // output prefix
            if (latex)
                ss << "\\begin{align*}";
            
            if (latex) {
                ss << "&" << "x_1≈" << roots.x1.stringLatexValue() << "," << "\\\\";
                ss << "&" << "x_2≈" << roots.x2.stringLatexValue() << "," << "\\\\";
                ss << "&" << "x_3≈" << roots.x3.stringLatexValue() << ".";
            }
            else {
                ss << "x1≈" << roots.x1.stringValue() << "," << "\n";
                ss << "x2≈" << roots.x2.stringValue() << "," << "\n";
                ss << "x3≈" << roots.x3.stringValue() << ".";
            }
            
            // output suffix
            if (latex)
                ss << "\\end{align*}";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}

#pragma mark - Multiple Unknowns

SolvingResult solveTwoUnknownsEquation(vector<string> &inputStrs, string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // a1x + b1y = c1
        // a2x + b2y = c2
        RationalNumber a1 = fractionFromString(inputStrs[0]);
        RationalNumber b1 = fractionFromString(inputStrs[1]);
        RationalNumber c1 = fractionFromString(inputStrs[2]);
        RationalNumber a2 = fractionFromString(inputStrs[3]);
        RationalNumber b2 = fractionFromString(inputStrs[4]);
        RationalNumber c2 = fractionFromString(inputStrs[5]);
        RationalNumber det = a1 * b2 - a2 * b1; // Discriminant of Cramer's Law
        
        if (det == 0) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            TwoUnknEquaParam params{
                a1, b1, c1,
                a2, b2, c2};
            TwoUnknEquaRt roots = rootOfTwoUnknownsEquation(params);
            stringstream ss;
            
            // output prefix
            if (latex)
                ss << "\\left\\{\\begin{align*}";
            
            // output x
            if (latex)
                ss << "&" << "x=" << roots.x.stringLatexValue();
            else
                ss << "x=" << roots.x.stringValue();
            
            if (!isInt(roots.x.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.x.doubleValue();
            }
            
            ss << "," << (latex ? "\\\\" : "\n");
            
            // output y
            if (latex)
                ss << "&" << "y=" << roots.y.stringLatexValue();
            else
                ss << "y=" << roots.y.stringValue();
            
            if (!isInt(roots.y.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.y.doubleValue();
            }
            
            ss << ".";
            
            // output suffix
            if (latex)
                ss << "\\end{align*}\\right.";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}

SolvingResult solveThreeUnknownsEquation(vector<string> &inputStrs, string &outputStr, bool latex) {
    removeBlanksFrom(inputStrs);
    
    if (!inputIsComplete((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersIncomplete;
    }
    else if (!inputIsValid((const vector<string>)inputStrs)) {
        return SolvingResultErrorParametersInvalid;
    }
    else {
        // a1x + b1y + c1z = d1
        // a2x + b2y + c2z = d2
        // a3x + b3y + c3z = d3
        RationalNumber a1 = fractionFromString(inputStrs[0]);
        RationalNumber b1 = fractionFromString(inputStrs[1]);
        RationalNumber c1 = fractionFromString(inputStrs[2]);
        RationalNumber d1 = fractionFromString(inputStrs[3]);
        RationalNumber a2 = fractionFromString(inputStrs[4]);
        RationalNumber b2 = fractionFromString(inputStrs[5]);
        RationalNumber c2 = fractionFromString(inputStrs[6]);
        RationalNumber d2 = fractionFromString(inputStrs[7]);
        RationalNumber a3 = fractionFromString(inputStrs[8]);
        RationalNumber b3 = fractionFromString(inputStrs[9]);
        RationalNumber c3 = fractionFromString(inputStrs[10]);
        RationalNumber d3 = fractionFromString(inputStrs[11]);
        RationalNumber det = a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1); // Discriminant of Cramer's Law
        
        if (det == 0) {
            return SolvingResultErrorCannotSolve;
        }
        else {
            ThreeUnknEquaParam params{
                a1, b1, c1, d1,
                a2, b2, c2, d2,
                a3, b3, c3, d3};
            ThreeUnknEquaRt roots = rootOfThreeUnknownsEquation(params);
            stringstream ss;
            
            // output prefix
            if (latex)
                ss << "\\left\\{\\begin{align*}";
            
            // output x
            if (latex)
                ss << "&" << "x=" << roots.x.stringLatexValue();
            else
                ss << "x=" << roots.x.stringValue();
            
            if (!isInt(roots.x.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.x.doubleValue();
            }
            
            ss << "," << (latex ? "\\\\" : "\n");
            
            // output y
            if (latex)
                ss << "&" << "y=" << roots.y.stringLatexValue();
            else
                ss << "y=" << roots.y.stringValue();
            
            if (!isInt(roots.y.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.y.doubleValue();
            }
            
            ss << "," << (latex ? "\\\\" : "\n");
            
            // output z
            if (latex)
                ss << "&" << "z=" << roots.z.stringLatexValue();
            else
                ss << "z=" << roots.z.stringValue();
            
            if (!isInt(roots.z.doubleValue())) {
                //ss << (latex ? "\\\\" : "\n");
                ss << "≈" << setiosflags(ios::fixed) << setprecision(6) << roots.z.doubleValue();
            }
            
            ss << ".";
            
            // output suffix
            if (latex)
                ss << "\\end{align*}\\right.";
            
            outputStr = ss.str();
        }
    }
    
    return SolvingResultSuccess;
}
