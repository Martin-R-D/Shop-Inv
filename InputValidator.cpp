#include "InputValidator.h"
#include <iostream>
#include <limits>

bool InputValidator::isPositiveInt(const string& input) {
    try {
        int val = stoi(input);
        return val > 0;
    } catch (...) { return false; }
}

bool InputValidator::isPositiveDouble(const string& input) {
    try {
        double val = stod(input);
        return val > 0;
    } catch (...) { return false; }
}

bool InputValidator::isNonEmpty(const string& input) {
    return !input.empty();
}

int InputValidator::getValidInt(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isPositiveInt(input)) return stoi(input);
        cout << "Invalid input. Enter a positive number." << endl;
    }
}

double InputValidator::getValidDouble(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isPositiveDouble(input)) return stod(input);
        cout << "Invalid input. Enter a positive number." << endl;
    }
}

string InputValidator::getValidString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isNonEmpty(input)) return input;
        cout << "Input cannot be empty." << endl;
    }
}
