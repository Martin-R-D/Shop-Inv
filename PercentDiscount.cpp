#include "PercentDiscount.h"

PercentDiscount::PercentDiscount(double percentage) : Discount(percentage) {}

double PercentDiscount::apply(double price) const {
    return price * (1.0 - value / 100.0);
}

bool PercentDiscount::isValid() const {
    return value > 0 && value <= 100;
}

string PercentDiscount::getDescription() const {
    return to_string((int)value) + "% off";
}