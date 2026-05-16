#include "Admin.h"

Admin::Admin(const string& name, const string& email, int adminLevel)
    : Person(name, email), adminLevel(adminLevel) {}

string Admin::getInfo() const {
    return "Admin: " + name + " | Email: " + email + " | Level: " + to_string(adminLevel);
}

int Admin::getAdminLevel() const { return adminLevel; }