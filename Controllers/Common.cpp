//
//  Common.cpp
//  MathTools
//
//  Created by Richard Chien on 7/15/15.
//
//

#include "Common.h"

using namespace std;

const string kRegexPatternInteger = "(^[\+]?[0-9]+[\.]?$)|(^\-[0-9]+[\.]?$)";
const string kRegexPatternDecimal = "(^[\+]?[0-9]*[\.][0-9]+$)|(^\-[0-9]*[\.][0-9]+$)";
const string kRegexPatternFraction = "^(([\+]?[0-9]+)|(\-[0-9]+))\/(([\+]?[0-9]+)|(\-[0-9]+))$";


#pragma mark - Action Methods
void removeBlanksFrom(string &str) {
    stringstream ss;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            ss << str[i];
    }
    str = ss.str();
}

void removeBlanksFrom(vector<string> &strs) {
    for (int i = 0; i < strs.size(); i++) {
        removeBlanksFrom(strs[i]);
    }
}

#pragma mark - Check Methods

bool inputIsComplete(const vector<string> &inputStrs) {
    for (int i = 0; i < inputStrs.size(); i++) {
        if (inputStrs[i].empty())
            return false;
    }
    return true;
}

bool isInteger(const string &str) {
    regex patternInteger(kRegexPatternInteger, regex_constants::extended);
    match_results<string::const_iterator> result;
    return regex_match(str, result, patternInteger);
}

bool isDecimal(const string &str) {
    regex patternDecimal(kRegexPatternDecimal, regex_constants::extended);
    match_results<string::const_iterator> result;
    return regex_match(str, result, patternDecimal);
}

bool isFraction(const string &str) {
    regex patternFraction(kRegexPatternFraction, regex_constants::extended);
    match_results<string::const_iterator> result;
    bool isValid = regex_match(str, result, patternFraction);
    if (isValid) {
        // Check if str is like x/0
        stringstream ss{str};
        long a;
        ss >> a;
        ss.ignore();
        ss >> a;
        if (a == 0)
            isValid = false;
    }
    return isValid;
}

bool isValid(const string &str) {
    return isDecimal(str) || isFraction(str) || isInteger(str);
}

bool inputIsValid(const vector<string> &inputStrs) {
    for (int i = 0; i < inputStrs.size(); i++) {
        if (!isValid(inputStrs[i]))
            return false;
    }
    return true;
}

#pragma mark - Convert Methods

RationalNumber fractionFromString(const std::string &str) {
    RationalNumber result;
    stringstream ss{str};
    if (isFraction(str)) {
        ss >> result.numerator;
        ss.ignore();
        ss >> result.denominator;
    }
    else if (isDecimal(str)) {
        double f = 0;
        ss >> f;
        result = frac(f);
    }
    else if (isInteger(str)) {
        ss >> result.numerator;
    }
    return result;
}

double doubleFromString(const std::string &str) {
    double f = 0;
    stringstream ss{str};
    if (isFraction(str)) {
        double a = 0, b = 0;
        ss >> a;
        ss.ignore();
        ss >> b;
        f = a / b;
    }
    else if (isDecimal(str) || isInteger(str)) {
        ss >> f;
    }
    return f;
}
