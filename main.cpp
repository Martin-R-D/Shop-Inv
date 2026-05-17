#include <iostream>
#include <limits>
#include "Store.h"
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void categoryMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Category Management ===" << endl;
        cout << "1. Add category" << endl;
        cout << "2. Edit category" << endl;
        cout << "3. Remove category" << endl;
        cout << "4. List categories" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1) {
            string name;
            cout << "Category name: "; getline(cin, name);
            store.addCategory(name);
        } else if (choice == 2) {
            int id; string name;
            cout << "Category ID: "; cin >> id; clearInput();
            cout << "New name: "; getline(cin, name);
            store.editCategory(id, name);
        } else if (choice == 3) {
            int id;
            cout << "Category ID: "; cin >> id; clearInput();
            store.removeCategory(id);
        } else if (choice == 4) {
            store.listCategories();
        }
    } while (choice != 0);
}

void productMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Product Management ===" << endl;
        cout << "1. Add physical product" << endl;
        cout << "2. Add service product" << endl;
        cout << "3. Edit product" << endl;
        cout << "4. Remove product" << endl;
        cout << "5. List products" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1) {
            string name, barcode; double price; int catId, qty, minStock;
            cout << "Name: "; getline(cin, name);
            cout << "Price: "; cin >> price; clearInput();
            cout << "Barcode: "; getline(cin, barcode);
            store.listCategories();
            cout << "Category ID: "; cin >> catId; clearInput();
            cout << "Quantity: "; cin >> qty; clearInput();
            cout << "Min stock alert: "; cin >> minStock; clearInput();
            store.addPhysicalProduct(name, price, barcode, catId, qty, minStock);
        } else if (choice == 2) {
            string name, barcode; double price; int catId, duration;
            cout << "Name: "; getline(cin, name);
            cout << "Price: "; cin >> price; clearInput();
            cout << "Barcode: "; getline(cin, barcode);
            store.listCategories();
            cout << "Category ID: "; cin >> catId; clearInput();
            cout << "Duration (min): "; cin >> duration; clearInput();
            store.addServiceProduct(name, price, barcode, catId, duration);
        } else if (choice == 3) {
            string name; double price; int id;
            store.listProducts();
            cout << "Product ID: "; cin >> id; clearInput();
            cout << "New name: "; getline(cin, name);
            cout << "New price: "; cin >> price; clearInput();
            store.editProduct(id, name, price);
        } else if (choice == 4) {
            int id;
            store.listProducts();
            cout << "Product ID: "; cin >> id; clearInput();
            store.removeProduct(id);
        } else if (choice == 5) {
            store.listProducts();
        }
    } while (choice != 0);
}

int main() {
    Store store;
    int choice;
    cout << "=== Shop Inventory & Cashier System ===" << endl;

    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Category management" << endl;
        cout << "2. Product management" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        switch (choice) {
            case 1: categoryMenu(store); break;
            case 2: productMenu(store); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}