//
//  EquationSolver.h
//  MathTools
//
//  Created by Richard Chien on 7/13/15.
//
//

#ifndef __MathTools__EquationSolver__
#define __MathTools__EquationSolver__

#include <iostream>
#include <string>
#include <vector>

#include "Common.h"

// One Unknown
SolvingResult solveLinearEquation(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveQuadraticEquation(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveCubicEquation(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);

// Multiple Unknowns
SolvingResult solveTwoUnknownsEquation(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveThreeUnknownsEquation(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);

#endif
