#pragma once
#include "Product.h"

class PhysicalProduct : public Product {
private:
    int quantity;
    int minStock;
public:
    PhysicalProduct(int id, const string& name, double price, const string& barcode, int categoryId, int quantity, int minStock);
    string getDetails() const override;
    string getType() const override;
    bool isLowStock() const;
    void restock(int qty);
    bool reduceStock(int qty);
    int getQuantity() const;
    int getMinStock() const;
    void setQuantity(int q);
    void setMinStock(int m);
};