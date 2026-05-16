#pragma once
#include "Person.h"

class Supplier : public Person {
private:
    string companyName;
public:
    Supplier(const string& name, const string& email, const string& companyName);
    string getInfo() const override;
    string getCompanyName() const;
    string getContactInfo() const;
};