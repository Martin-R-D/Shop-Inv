#include "TransactionItem.h"

TransactionItem::TransactionItem(Product* product, int quantity)
    : product(product), quantity(quantity), unitPrice(product->getPrice()), discount(nullptr) {}

double TransactionItem::getSubtotal() const {
    double total = unitPrice * quantity;
    if (discount && discount->isValid()) {
        total = discount->apply(total);
    }
    return total;
}

void TransactionItem::applyDiscount(Discount* d) { discount = d; }
Product* TransactionItem::getProduct() const { return product; }
int TransactionItem::getQuantity() const { return quantity; }
double TransactionItem::getUnitPrice() const { return unitPrice; }
Discount* TransactionItem::getDiscount() const { return discount; }