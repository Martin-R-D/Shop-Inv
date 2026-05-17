#include "Store.h"
#include <iostream>
#include <algorithm>
#include <ctime>

Store::Store() : nextTransactionId(1), nextCategoryId(1), nextProductId(1) {}

Store::~Store() {
    for (auto* c : categories) delete c;
    for (auto* p : products) delete p;
    for (auto* t : transactions) delete t;
}

void Store::addCategory(const string& name) {
    categories.push_back(new Category(nextCategoryId++, name));
    cout << "Category added successfully." << endl;
}

void Store::editCategory(int id, const string& newName) {
    Category* c = findCategory(id);
    if (c) { c->setName(newName); cout << "Category updated." << endl; }
    else cout << "Category not found." << endl;
}

void Store::removeCategory(int id) {
    for (const auto* p : products) {
        if (p->getCategoryId() == id) {
            cout << "Cannot remove: products still use this category." << endl;
            return;
        }
    }
    auto it = find_if(categories.begin(), categories.end(),
        [id](const Category* c) { return c->getId() == id; });
    if (it != categories.end()) {
        delete *it;
        categories.erase(it);
        cout << "Category removed." << endl;
    } else cout << "Category not found." << endl;
}

void Store::listCategories() const {
    if (categories.empty()) { cout << "No categories." << endl; return; }
    cout << "\n--- Categories ---" << endl;
    for (const auto* c : categories)
        cout << "  [" << c->getId() << "] " << c->getName() << endl;
}

Category* Store::findCategory(int id) const {
    for (auto* c : categories) if (c->getId() == id) return c;
    return nullptr;
}

void Store::addPhysicalProduct(const string& name, double price, const string& barcode, int categoryId, int qty, int minStock) {
    if (!findCategory(categoryId)) { cout << "Category not found." << endl; return; }
    products.push_back(new PhysicalProduct(nextProductId++, name, price, barcode, categoryId, qty, minStock));
    cout << "Physical product added." << endl;
}

void Store::addServiceProduct(const string& name, double price, const string& barcode, int categoryId, int duration) {
    if (!findCategory(categoryId)) { cout << "Category not found." << endl; return; }
    products.push_back(new ServiceProduct(nextProductId++, name, price, barcode, categoryId, duration));
    cout << "Service product added." << endl;
}

void Store::editProduct(int id, const string& newName, double newPrice) {
    Product* p = findProduct(id);
    if (p) { p->setName(newName); p->setPrice(newPrice); cout << "Product updated." << endl; }
    else cout << "Product not found." << endl;
}

void Store::removeProduct(int id) {
    auto it = find_if(products.begin(), products.end(),
        [id](const Product* p) { return p->getId() == id; });
    if (it != products.end()) {
        delete *it;
        products.erase(it);
        cout << "Product removed." << endl;
    } else cout << "Product not found." << endl;
}

void Store::listProducts() const {
    if (products.empty()) { cout << "No products." << endl; return; }
    cout << "\n--- Products ---" << endl;
    for (const auto* p : products) {
        Category* cat = findCategory(p->getCategoryId());
        string catName = cat ? cat->getName() : "Unknown";
        cout << "  [" << p->getId() << "] " << p->getDetails()
             << " | Category: " << catName << endl;
    }
}

Product* Store::findProduct(int id) const {
    for (auto* p : products) if (p->getId() == id) return p;
    return nullptr;
}

Product* Store::findProductByBarcode(const string& barcode) const {
    for (auto* p : products) if (p->getBarcode() == barcode) return p;
    return nullptr;
}

const vector<Product*>& Store::getProducts() const { return products; }
const vector<Category*>& Store::getCategories() const { return categories; }

void Store::checkLowStock() const {
    bool found = false;
    cout << "\n--- Low Stock Alerts ---" << endl;
    for (const auto* p : products) {
        const PhysicalProduct* pp = dynamic_cast<const PhysicalProduct*>(p);
        if (pp && pp->isLowStock()) {
            cout << "  WARNING: [" << pp->getId() << "] " << pp->getName()
                 << " - Qty: " << pp->getQuantity()
                 << " (min: " << pp->getMinStock() << ")" << endl;
            found = true;
        }
    }
    if (!found) cout << "  All stock levels are OK." << endl;
}

void Store::restockProduct(int productId, int qty) {
    Product* p = findProduct(productId);
    if (!p) { cout << "Product not found." << endl; return; }
    PhysicalProduct* pp = dynamic_cast<PhysicalProduct*>(p);
    if (!pp) { cout << "Only physical products can be restocked." << endl; return; }
    pp->restock(qty);
    cout << "Restocked " << pp->getName() << ". New quantity: " << pp->getQuantity() << endl;
}

void Store::showInventorySummary() const {
    int totalPhysical = 0, totalService = 0, totalUnits = 0;
    double totalValue = 0;
    for (const auto* p : products) {
        const PhysicalProduct* pp = dynamic_cast<const PhysicalProduct*>(p);
        if (pp) {
            totalPhysical++;
            totalUnits += pp->getQuantity();
            totalValue += pp->getQuantity() * pp->getPrice();
        } else {
            totalService++;
        }
    }
    cout << "\n--- Inventory Summary ---" << endl;
    cout << "  Physical products: " << totalPhysical << endl;
    cout << "  Service products: " << totalService << endl;
    cout << "  Total units in stock: " << totalUnits << endl;
    cout << "  Total inventory value: " << totalValue << endl;
    cout << "  Categories: " << categories.size() << endl;
}



Transaction* Store::createTransaction(const string& paymentMethod) {
    time_t now = time(0);
    string date = ctime(&now);
    date.pop_back(); // remove newline
    Transaction* t = new Transaction(nextTransactionId++, date, paymentMethod);
    return t;
}

void Store::addItemToTransaction(Transaction* t, int productId, int qty) {
    Product* p = findProduct(productId);
    if (!p) { cout << "Product not found." << endl; return; }

    PhysicalProduct* pp = dynamic_cast<PhysicalProduct*>(p);
    if (pp) {
        if (!pp->reduceStock(qty)) {
            cout << "Not enough stock. Available: " << pp->getQuantity() << endl;
            return;
        }
    }

    TransactionItem item(p, qty);
    t->addItem(item);
    cout << "Added " << p->getName() << " x" << qty << endl;
}

void Store::finalizeTransaction(Transaction* t) {
    t->calculateTotal();
    transactions.push_back(t);
    cout << t->generateReceipt();
}

void Store::listTransactions() const {
    if (transactions.empty()) { cout << "No transactions." << endl; return; }
    cout << "\n--- Transaction History ---" << endl;
    for (const auto* t : transactions) {
        cout << "  [#" << t->getId() << "] " << t->getDate()
             << " | " << t->getPaymentMethod()
             << " | Total: " << t->getTotalAmount() << endl;
    }
}