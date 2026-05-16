#pragma once
#include <string>
using namespace std;

class Discount {
protected:
    double value;
public:
    Discount(double value);
    virtual ~Discount() = default;
    virtual double apply(double price) const = 0;
    virtual bool isValid() const = 0;
    virtual string getDescription() const = 0;
    double getValue() const;
};