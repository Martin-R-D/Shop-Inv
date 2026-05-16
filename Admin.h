#pragma once
#include "Person.h"

class Admin : public Person {
private:
    int adminLevel;
public:
    Admin(const string& name, const string& email, int adminLevel);
    string getInfo() const override;
    int getAdminLevel() const;
};