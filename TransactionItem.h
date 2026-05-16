#pragma once
#include "Product.h"
#include "Discount.h"

class TransactionItem {
private:
    Product* product;
    int quantity;
    double unitPrice;
    Discount* discount;
public:
    TransactionItem(Product* product, int quantity);
    double getSubtotal() const;
    void applyDiscount(Discount* d);
    Product* getProduct() const;
    int getQuantity() const;
    double getUnitPrice() const;
    Discount* getDiscount() const;
};