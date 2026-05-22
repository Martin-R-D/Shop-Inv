#pragma once
#include <string>
using namespace std;

class InputValidator {
public:
    static bool isPositiveInt(const string& input);
    static bool isPositiveDouble(const string& input);
    static bool isNonEmpty(const string& input);
    static int getValidInt(const string& prompt);
    static double getValidDouble(const string& prompt);
    static string getValidString(const string& prompt);
};
