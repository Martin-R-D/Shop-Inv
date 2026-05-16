#include "Supplier.h"

Supplier::Supplier(const string& name, const string& email, const string& companyName)
    : Person(name, email), companyName(companyName) {}

string Supplier::getInfo() const {
    return "Supplier: " + name + " | Company: " + companyName + " | Email: " + email;
}

string Supplier::getCompanyName() const { return companyName; }

string Supplier::getContactInfo() const {
    return name + " (" + companyName + ") - " + email;
}