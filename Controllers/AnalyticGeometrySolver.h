//
//  AnalyticGeometrySolver.h
//  MathTools
//
//  Created by Richard Chien on 7/13/15.
//
//

#ifndef __MathTools__AnalyticGeometrySolver__
#define __MathTools__AnalyticGeometrySolver__

#include <iostream>
#include <string>
#include <vector>

#include "Common.h"

// Solve to Get Expression
SolvingResult solveLineWithTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveCircleWithThreePoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveEllipseWithTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveQuadraticFunctionWithThreePoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);

// Solve to Get Distance
SolvingResult solveDistanceBetweenTwoPoints(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);
SolvingResult solveDistanceBetweenPointAndLine(std::vector<std::string> &inputStrs, std::string &outputStr, bool latex);

#endif
