#pragma once
#include "Discount.h"

class FixedDiscount : public Discount {
public:
    FixedDiscount(double amount);
    double apply(double price) const override;
    bool isValid() const override;
    string getDescription() const override;
};