#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(int id, const string& date, const string& paymentMethod)
    : id(id), date(date), totalAmount(0), paymentMethod(paymentMethod) {}

void Transaction::addItem(const TransactionItem& item) {
    items.push_back(item);
}

double Transaction::calculateTotal() {
    totalAmount = 0;
    for (const auto& item : items) {
        totalAmount += item.getSubtotal();
    }
    return totalAmount;
}

string Transaction::generateReceipt() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "========== RECEIPT ==========" << endl;
    ss << "Transaction #" << id << endl;
    ss << "Date: " << date << endl;
    ss << "Payment: " << paymentMethod << endl;
    ss << "-----------------------------" << endl;
    for (const auto& item : items) {
        ss << item.getProduct()->getName()
           << " x" << item.getQuantity()
           << " @ " << item.getUnitPrice();
        if (item.getDiscount() && item.getDiscount()->isValid()) {
            ss << " (" << item.getDiscount()->getDescription() << ")";
        }
        ss << " = " << item.getSubtotal() << endl;
    }
    ss << "-----------------------------" << endl;
    ss << "TOTAL: " << totalAmount << endl;
    ss << "=============================" << endl;
    return ss.str();
}

void Transaction::cancel() {
    items.clear();
    totalAmount = 0;
}

int Transaction::getId() const { return id; }
string Transaction::getDate() const { return date; }
double Transaction::getTotalAmount() const { return totalAmount; }
string Transaction::getPaymentMethod() const { return paymentMethod; }
const vector<TransactionItem>& Transaction::getItems() const { return items; }