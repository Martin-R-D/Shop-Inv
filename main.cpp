#include <iostream>
#include "Store.h"
#include "AuthManager.h"
#include "FileManager.h"
#include "MenuHelpers.h"
#include "SampleData.h"
using namespace std;

int main() {
    Store store;
    AuthManager auth;

    auth.addAdmin("Ivan", "ivan@shop.bg", 1);
    auth.addCashier("Maria", "maria@shop.bg", "morning");

    SampleData::seed(store);

    FileManager::loadCategories(store, "categories.txt");
    FileManager::loadProducts(store, "products.txt");

    string name, role;
    cout << "=== Shop Inventory & Cashier System ===" << endl;
    cout << "Login name: "; getline(cin, name);
    cout << "Role (admin/cashier): "; getline(cin, role);

    if (!auth.login(name, role)) {
        cout << "Login failed." << endl;
        return 1;
    }

    int choice;
    do {
        cout << "\n=== Main Menu [" << auth.getCurrentUser() << " - " << auth.getCurrentRole() << "] ===" << endl;
        cout << "1. Category management" << endl;
        cout << "2. Product management" << endl;
        cout << "3. Inventory management" << endl;
        cout << "4. Sales" << endl;
        cout << "5. Deliveries" << endl;
        cout << "6. Search" << endl;
        if (auth.isAdmin()) {
            cout << "7. Reports" << endl;
            cout << "8. User management" << endl;
        }
        cout << "9. Save data" << endl;
        cout << "0. Logout & Exit" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        switch (choice) {
            case 1: categoryMenu(store); break;
            case 2: productMenu(store); break;
            case 3: inventoryMenu(store); break;
            case 4: salesMenu(store); break;
            case 5: deliveryMenu(store); break;
            case 6: searchMenu(store); break;
            case 7:
                if (auth.isAdmin()) reportsMenu(store);
                else cout << "Access denied." << endl;
                break;
            case 8:
                if (auth.isAdmin()) auth.listUsers();
                else cout << "Access denied." << endl;
                break;
            case 9:
                FileManager::saveCategories(store, "categories.txt");
                FileManager::saveProducts(store, "products.txt");
                FileManager::saveTransactions(store, "transactions.txt");
                cout << "Data saved." << endl;
                break;
            case 0:
                FileManager::saveCategories(store, "categories.txt");
                FileManager::saveProducts(store, "products.txt");
                FileManager::saveTransactions(store, "transactions.txt");
                auth.logout();
                cout << "Data saved. Goodbye!" << endl;
                break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
