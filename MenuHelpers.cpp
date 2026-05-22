#include "MenuHelpers.h"
#include "ReportManager.h"
#include "PercentDiscount.h"
#include "FixedDiscount.h"
#include "InputValidator.h"
#include "HtmlReport.h"
#include <iostream>
#include <limits>
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
            string name = InputValidator::getValidString("Category name: ");
            store.addCategory(name);
        } else if (choice == 2) {
            int id = InputValidator::getValidInt("Category ID: ");
            string name = InputValidator::getValidString("New name: ");
            store.editCategory(id, name);
        } else if (choice == 3) {
            int id = InputValidator::getValidInt("Category ID: ");
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
            string name = InputValidator::getValidString("Name: ");
            double price = InputValidator::getValidDouble("Price: ");
            string barcode = InputValidator::getValidString("Barcode: ");
            store.listCategories();
            int catId = InputValidator::getValidInt("Category ID: ");
            int qty = InputValidator::getValidInt("Quantity: ");
            int minStock = InputValidator::getValidInt("Min stock alert: ");
            store.addPhysicalProduct(name, price, barcode, catId, qty, minStock);
        } else if (choice == 2) {
            string name = InputValidator::getValidString("Name: ");
            double price = InputValidator::getValidDouble("Price: ");
            string barcode = InputValidator::getValidString("Barcode: ");
            store.listCategories();
            int catId = InputValidator::getValidInt("Category ID: ");
            int duration = InputValidator::getValidInt("Duration (min): ");
            store.addServiceProduct(name, price, barcode, catId, duration);
        } else if (choice == 3) {
            store.listProducts();
            int id = InputValidator::getValidInt("Product ID: ");
            string name = InputValidator::getValidString("New name: ");
            double price = InputValidator::getValidDouble("New price: ");
            store.editProduct(id, name, price);
        } else if (choice == 4) {
            store.listProducts();
            int id = InputValidator::getValidInt("Product ID: ");
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
            store.listProducts();
            int id = InputValidator::getValidInt("Product ID: ");
            int qty = InputValidator::getValidInt("Quantity to add: ");
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
            string payment = InputValidator::getValidString("Payment method (cash/card): ");
            Transaction* t = store.createTransaction(payment);

            int addMore = 1;
            while (addMore) {
                store.listProducts();
                int prodId = InputValidator::getValidInt("Product ID: ");
                int qty = InputValidator::getValidInt("Quantity: ");
                store.addItemToTransaction(t, prodId, qty);

                if (choice == 2) {
                    int discType;
                    cout << "Discount? (1=percent, 2=fixed, 0=none): ";
                    cin >> discType; clearInput();
                    if (discType == 1) {
                        double val = InputValidator::getValidDouble("Percent: ");
                        Discount* d = new PercentDiscount(val);
                        store.applyDiscountToTransaction(t, t->getItems().size() - 1, d);
                    } else if (discType == 2) {
                        double val = InputValidator::getValidDouble("Amount: ");
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

void deliveryMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Deliveries ===" << endl;
        cout << "1. Add supplier" << endl;
        cout << "2. List suppliers" << endl;
        cout << "3. Create delivery" << endl;
        cout << "4. Receive delivery" << endl;
        cout << "5. List deliveries" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name = InputValidator::getValidString("Name: ");
            string email = InputValidator::getValidString("Email: ");
            string company = InputValidator::getValidString("Company: ");
            store.addSupplier(name, email, company);
        } else if (choice == 2) {
            store.listSuppliers();
        } else if (choice == 3) {
            store.listSuppliers();
            int idx = InputValidator::getValidInt("Supplier #: ");
            store.createDelivery(idx);
        } else if (choice == 4) {
            store.listDeliveries();
            int id = InputValidator::getValidInt("Delivery ID: ");
            store.receiveDelivery(id);
        } else if (choice == 5) {
            store.listDeliveries();
        }
    } while (choice != 0);
}

void reportsMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Reports ===" << endl;
        cout << "1. Revenue by period" << endl;
        cout << "2. Top selling products" << endl;
        cout << "3. Inventory value" << endl;
        cout << "4. Transaction summary (cash vs card)" << endl;
        cout << "5. Export product report (HTML)" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1) {
            string date;
            cout << "Date filter (or empty for all): "; getline(cin, date);
            ReportManager::revenueByPeriod(store, date);
        } else if (choice == 2) {
            int n = InputValidator::getValidInt("How many top products: ");
            ReportManager::topSellingProducts(store, n);
        } else if (choice == 3) {
            ReportManager::inventoryValue(store);
        } else if (choice == 4) {
            ReportManager::transactionSummary(store);
        } else if (choice == 5) {
            HtmlReport::generateProductReport(store, "product_report.html");
        }
    } while (choice != 0);
}

void searchMenu(Store& store) {
    int choice;
    do {
        cout << "\n=== Search ===" << endl;
        cout << "1. Search by barcode" << endl;
        cout << "2. Filter by category" << endl;
        cout << "3. Search by name" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice; clearInput();

        if (choice == 1) {
            string bc = InputValidator::getValidString("Barcode: ");
            store.searchByBarcode(bc);
        } else if (choice == 2) {
            store.listCategories();
            int catId = InputValidator::getValidInt("Category ID: ");
            store.filterByCategory(catId);
        } else if (choice == 3) {
            string kw = InputValidator::getValidString("Keyword: ");
            store.searchByName(kw);
        }
    } while (choice != 0);
}
