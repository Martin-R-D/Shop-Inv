#pragma once
#include "Discount.h"

class PercentDiscount : public Discount {
public:
    PercentDiscount(double percentage);
    double apply(double price) const override;
    bool isValid() const override;
    string getDescription() const override;
};
