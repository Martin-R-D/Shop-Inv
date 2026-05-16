#include "Cashier.h"

Cashier::Cashier(const string& name, const string& email, const string& shift)
    : Person(name, email), shift(shift) {}

string Cashier::getInfo() const {
    return "Cashier: " + name + " | Email: " + email + " | Shift: " + shift;
}

string Cashier::getShift() const { return shift; }