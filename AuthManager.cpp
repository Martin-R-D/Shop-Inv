#include "AuthManager.h"
#include <iostream>

AuthManager::AuthManager() : currentRole(""), currentUser("") {}

AuthManager::~AuthManager() {
    for (auto* a : admins) delete a;
    for (auto* c : cashiers) delete c;
}

void AuthManager::addAdmin(const string& name, const string& email, int level) {
    admins.push_back(new Admin(name, email, level));
    cout << "Admin added." << endl;
}

void AuthManager::addCashier(const string& name, const string& email, const string& shift) {
    cashiers.push_back(new Cashier(name, email, shift));
    cout << "Cashier added." << endl;
}

bool AuthManager::login(const string& name) {
    for (const auto* a : admins) {
        if (a->getName() == name) {
            currentUser = name;
            currentRole = "admin";
            cout << "Logged in as admin: " << name << endl;
            return true;
        }
    }
    for (const auto* c : cashiers) {
        if (c->getName() == name) {
            currentUser = name;
            currentRole = "cashier";
            cout << "Logged in as cashier: " << name << endl;
            return true;
        }
    }
    cout << "User not found." << endl;
    return false;
}

bool AuthManager::registerUser(const string& name, const string& email, const string& role, const string& extra) {
    if (userExists(name)) {
        cout << "User already exists." << endl;
        return false;
    }
    if (role == "admin") {
        int level = 1;
        try { level = stoi(extra); } catch (...) {}
        addAdmin(name, email, level);
        return true;
    } else if (role == "cashier") {
        addCashier(name, email, extra.empty() ? "morning" : extra);
        return true;
    }
    cout << "Invalid role." << endl;
    return false;
}

bool AuthManager::userExists(const string& name) const {
    for (const auto* a : admins)
        if (a->getName() == name) return true;
    for (const auto* c : cashiers)
        if (c->getName() == name) return true;
    return false;
}

void AuthManager::logout() {
    cout << currentUser << " logged out." << endl;
    currentUser = "";
    currentRole = "";
}

bool AuthManager::isAdmin() const { return currentRole == "admin"; }
bool AuthManager::isCashier() const { return currentRole == "cashier"; }
bool AuthManager::isLoggedIn() const { return !currentRole.empty(); }
string AuthManager::getCurrentUser() const { return currentUser; }
string AuthManager::getCurrentRole() const { return currentRole; }

void AuthManager::listUsers() const {
    cout << "\n--- Admins ---" << endl;
    for (const auto* a : admins) cout << "  " << a->getInfo() << endl;
    cout << "--- Cashiers ---" << endl;
    for (const auto* c : cashiers) cout << "  " << c->getInfo() << endl;
}
