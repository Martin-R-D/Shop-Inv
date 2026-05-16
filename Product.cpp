#include "Product.h"

Product::Product(int id, const string& name, double price, const string& barcode, int categoryId)
    : id(id), name(name), price(price), barcode(barcode), categoryId(categoryId) {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
string Product::getBarcode() const { return barcode; }
int Product::getCategoryId() const { return categoryId; }
void Product::setName(const string& n) { name = n; }
void Product::setPrice(double p) { if (p >= 0) price = p; }
void Product::setBarcode(const string& b) { barcode = b; }
void Product::setCategoryId(int cId) { categoryId = cId; }