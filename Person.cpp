#include "Person.h"

Person::Person(const string& name, const string& email): name(name), email(email) {}

string Person::getName() const { return name; }
string Person::getEmail() const { return email; }