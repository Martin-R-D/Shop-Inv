#pragma once
#include "Person.h"

class Cashier : public Person {
private:
    string shift;
public:
    Cashier(const string& name, const string& email, const string& shift);
    string getInfo() const override;
    string getShift() const;
};