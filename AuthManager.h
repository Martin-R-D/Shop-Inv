#pragma once
#include "Admin.h"
#include "Cashier.h"
#include <vector>
#include <string>
using namespace std;

class AuthManager {
private:
    vector<Admin*> admins;
    vector<Cashier*> cashiers;
    string currentRole;
    string currentUser;
public:
    AuthManager();
    ~AuthManager();
    void addAdmin(const string& name, const string& email, int level);
    void addCashier(const string& name, const string& email, const string& shift);
    bool login(const string& name);
    bool registerUser(const string& name, const string& email, const string& role, const string& extra);
    bool userExists(const string& name) const;
    void logout();
    bool isAdmin() const;
    bool isCashier() const;
    bool isLoggedIn() const;
    string getCurrentUser() const;
    string getCurrentRole() const;
    void listUsers() const;
};
