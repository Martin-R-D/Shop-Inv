#include "Admin.h"

Admin::Admin(const string& name, const string& email)
    : Person(name, email) {}

string Admin::getInfo() const {
    return "Admin: " + name + " | Email: " + email;
}
