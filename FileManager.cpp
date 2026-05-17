#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

void FileManager::saveCategories(const Store& store, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) { cout << "Error saving categories." << endl; return; }
    for (const auto* c : store.getCategories()) {
        file << c->getId() << "|" << c->getName() << endl;
    }
    file.close();
    cout << "Categories saved." << endl;
}

void FileManager::saveProducts(const Store& store, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) { cout << "Error saving products." << endl; return; }
    for (const auto* p : store.getProducts()) {
        file << p->getId() << "|" << p->getType() << "|" << p->getName() << "|"
             << p->getPrice() << "|" << p->getBarcode() << "|" << p->getCategoryId();
        const PhysicalProduct* pp = dynamic_cast<const PhysicalProduct*>(p);
        if (pp) {
            file << "|" << pp->getQuantity() << "|" << pp->getMinStock();
        }
        const ServiceProduct* sp = dynamic_cast<const ServiceProduct*>(p);
        if (sp) {
            file << "|" << sp->getDuration();
        }
        file << endl;
    }
    file.close();
    cout << "Products saved." << endl;
}

void FileManager::saveTransactions(const Store& store, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) { cout << "Error saving transactions." << endl; return; }
    for (const auto* t : store.getTransactions()) {
        file << t->getId() << "|" << t->getDate() << "|"
             << t->getPaymentMethod() << "|" << t->getTotalAmount() << endl;
        for (const auto& item : t->getItems()) {
            file << "  ITEM|" << item.getProduct()->getId() << "|"
                 << item.getQuantity() << "|" << item.getSubtotal() << endl;
        }
    }
    file.close();
    cout << "Transactions saved." << endl;
}

void FileManager::loadCategories(Store& store, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name;
        getline(ss, idStr, '|');
        getline(ss, name, '|');
        store.addCategory(name);
    }
    file.close();
    cout << "Categories loaded." << endl;
}

void FileManager::loadProducts(Store& store, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, type, name, priceStr, barcode, catIdStr;
        getline(ss, idStr, '|');
        getline(ss, type, '|');
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, barcode, '|');
        getline(ss, catIdStr, '|');

        double price = stod(priceStr);
        int catId = stoi(catIdStr);

        if (type == "physical") {
            string qtyStr, minStr;
            getline(ss, qtyStr, '|');
            getline(ss, minStr, '|');
            store.addPhysicalProduct(name, price, barcode, catId, stoi(qtyStr), stoi(minStr));
        } else {
            string durStr;
            getline(ss, durStr, '|');
            store.addServiceProduct(name, price, barcode, catId, stoi(durStr));
        }
    }
    file.close();
    cout << "Products loaded." << endl;
}