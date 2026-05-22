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

bool AuthManager::login(const string& name, const string& role) {
    if (role == "admin") {
        for (const auto* a : admins) {
            if (a->getName() == name) {
                currentUser = name;
                currentRole = "admin";
                cout << "Logged in as admin: " << name << endl;
                return true;
            }
        }
    } else if (role == "cashier") {
        for (const auto* c : cashiers) {
            if (c->getName() == name) {
                currentUser = name;
                currentRole = "cashier";
                cout << "Logged in as cashier: " << name << endl;
                return true;
            }
        }
    }
    cout << "User not found." << endl;
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
