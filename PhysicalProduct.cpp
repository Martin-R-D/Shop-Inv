#include "PhysicalProduct.h"

PhysicalProduct::PhysicalProduct(int id, const string& name, double price, const string& barcode, int categoryId, int quantity, int minStock)
    : Product(id, name, price, barcode, categoryId), quantity(quantity), minStock(minStock) {}

string PhysicalProduct::getDetails() const {
    return "[Physical] " + name + " | Price: " + to_string(price) + " | Qty: " + to_string(quantity) + " | Barcode: " + barcode;
}

string PhysicalProduct::getType() const { return "physical"; }
bool PhysicalProduct::isLowStock() const { return quantity <= minStock; }
void PhysicalProduct::restock(int qty) { if (qty > 0) quantity += qty; }

bool PhysicalProduct::reduceStock(int qty) {
    if (qty > 0 && quantity >= qty) {
        quantity -= qty;
        return true;
    }
    return false;
}

int PhysicalProduct::getQuantity() const { return quantity; }
int PhysicalProduct::getMinStock() const { return minStock; }
void PhysicalProduct::setQuantity(int q) { if (q >= 0) quantity = q; }
void PhysicalProduct::setMinStock(int m) { if (m >= 0) minStock = m; }