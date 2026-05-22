#pragma once
#include "Person.h"

class Admin : public Person {
public:
    Admin(const string& name, const string& email);
    string getInfo() const override;
};
