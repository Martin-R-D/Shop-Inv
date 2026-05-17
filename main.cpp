#include <iostream>
#include <limits>
#include "Store.h"
#include "FileManager.h"
#include "PercentDiscount.h"
#include "FixedDiscount.h"
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

void inventoryMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Inventory Management ===" << endl;
        cout << "1. Check low stock alerts" << endl;
        cout << "2. Restock a product" << endl;
        cout << "3. Inventory summary" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1) {
            store.checkLowStock();
        } else if (choice == 2) {
            int id, qty;
            store.listProducts();
            cout << "Product ID: "; cin >> id; clearInput();
            cout << "Quantity to add: "; cin >> qty; clearInput();
            store.restockProduct(id, qty);
        } else if (choice == 3) {
            store.showInventorySummary();
        }
    } while (choice != 0);
}


void salesMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Sales ===" << endl;
        cout << "1. New sale" << endl;
        cout << "2. New sale with discount" << endl;
        cout << "3. View transaction history" << endl;
        cout << "4. Filter transactions by date" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1 || choice == 2) {
            string payment;
            cout << "Payment method (cash/card): "; getline(cin, payment);
            Transaction* t = store.createTransaction(payment);

            int addMore = 1;
            while (addMore) {
                store.listProducts();
                int prodId, qty;
                cout << "Product ID: "; cin >> prodId; clearInput();
                cout << "Quantity: "; cin >> qty; clearInput();
                store.addItemToTransaction(t, prodId, qty);

                if (choice == 2) {
                    int discType;
                    double val;
                    cout << "Discount? (1=percent, 2=fixed, 0=none): ";
                    cin >> discType; clearInput();
                    if (discType == 1) {
                        cout << "Percent: "; cin >> val; clearInput();
                        Discount* d = new PercentDiscount(val);
                        store.applyDiscountToTransaction(t, t->getItems().size() - 1, d);
                    } else if (discType == 2) {
                        cout << "Amount: "; cin >> val; clearInput();
                        Discount* d = new FixedDiscount(val);
                        store.applyDiscountToTransaction(t, t->getItems().size() - 1, d);
                    }
                }

                cout << "Add another? (1=yes, 0=no): "; cin >> addMore; clearInput();
            }
            store.finalizeTransaction(t);
        } else if (choice == 3) {
            store.listTransactions();
        } else if (choice == 4) {
            string date;
            cout << "Date to search: "; getline(cin, date);
            auto results = store.filterTransactionsByDate(date);
            if (results.empty()) { cout << "No transactions found." << endl; }
            else {
                for (const auto* t : results)
                    cout << "  [#" << t->getId() << "] " << t->getDate()
                         << " | Total: " << t->getTotalAmount() << endl;
            }
        }
    } while (choice != 0);
}

int main() {
    Store store;

    
    FileManager::loadCategories(store, "categories.txt");
    FileManager::loadProducts(store, "products.txt");

    int choice;
    cout << "=== Shop Inventory & Cashier System ===" << endl;

    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Category management" << endl;
        cout << "2. Product management" << endl;
        cout << "3. Inventory management" << endl;
        cout << "4. Sales" << endl;
        cout << "5. Save data" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        switch (choice) {
            case 1: categoryMenu(store); break;
            case 2: productMenu(store); break;
            case 3: inventoryMenu(store); break;
            case 4: salesMenu(store); break;
            case 5:
                FileManager::saveCategories(store, "categories.txt");
                FileManager::saveProducts(store, "products.txt");
                FileManager::saveTransactions(store, "transactions.txt");
                break;
            case 0:
                FileManager::saveCategories(store, "categories.txt");
                FileManager::saveProducts(store, "products.txt");
                FileManager::saveTransactions(store, "transactions.txt");
                cout << "Data saved. Goodbye!" << endl;
                break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}