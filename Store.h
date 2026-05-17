#pragma once
#include "Category.h"
#include "Product.h"
#include "PhysicalProduct.h"
#include "ServiceProduct.h"
#include <vector>
#include <string>
using namespace std;

class Store {
private:
    vector<Category*> categories;
    vector<Product*> products;
    int nextCategoryId;
    int nextProductId;
public:
    Store();
    ~Store();

    void addCategory(const string& name);
    void editCategory(int id, const string& newName);
    void removeCategory(int id);
    void listCategories() const;
    Category* findCategory(int id) const;

    void addPhysicalProduct(const string& name, double price, const string& barcode, int categoryId, int qty, int minStock);
    void addServiceProduct(const string& name, double price, const string& barcode, int categoryId, int duration);
    void editProduct(int id, const string& newName, double newPrice);
    void removeProduct(int id);
    void listProducts() const;
    Product* findProduct(int id) const;
    Product* findProductByBarcode(const string& barcode) const;

    const vector<Product*>& getProducts() const;
    const vector<Category*>& getCategories() const;

    void checkLowStock() const;
    void restockProduct(int productId, int qty);
    void showInventorySummary() const;
};