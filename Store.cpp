#include "Store.h"
#include <iostream>
#include <algorithm>

Store::Store() : nextCategoryId(1), nextProductId(1) {}

Store::~Store() {
    for (auto* c : categories) delete c;
    for (auto* p : products) delete p;
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