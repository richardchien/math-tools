//
//  Common.h
//  MathTools
//
//  Created by Richard Chien on 7/15/15.
//
//

#ifndef __MathTools__Common__
#define __MathTools__Common__

#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "../Models/MathToolsModels.h"

typedef enum {
    SolvingResultSuccess,
    SolvingResultErrorParametersIncomplete, // Input has empty item(s)
    SolvingResultErrorParametersInvalid, // Input is not valid number or is something like x/0
    SolvingResultErrorCannotSolve // Can not solve with the given parameters
} SolvingResult;

// Action Methods
void removeBlanksFrom(std::string &str);
void removeBlanksFrom(std::vector<std::string> &strs);

// Check Methods
bool isInteger(const std::string &str);
bool isDecimal(const std::string &str);
bool isFraction(const std::string &str);
//// Check if input string is valid number which can be read
bool isValid(const std::string &str);
//// Check if input is complete or not, parameter 'inputStrs' is the input array without blanks
bool inputIsComplete(const std::vector<std::string> &inputStrs);
//// Check if input is valid or not, parameter 'inputStrs' is the input array without blanks
bool inputIsValid(const std::vector<std::string> &inputStrs);

// Convert Method
// These methods do not do validation check
RationalNumber fractionFromString(const std::string &str);
double doubleFromString(const std::string &str);

#endif
