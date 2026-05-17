#include "FixedDiscount.h"

FixedDiscount::FixedDiscount(double amount) : Discount(amount) {}

double FixedDiscount::apply(double price) const {
    double result = price - value;
    return result > 0 ? result : 0;
}

bool FixedDiscount::isValid() const { return value > 0; }

string FixedDiscount::getDescription() const {
    return to_string((int)value) + " off";
}