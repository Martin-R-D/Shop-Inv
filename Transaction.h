#pragma once
#include "TransactionItem.h"
#include <vector>
#include <string>
using namespace std;

class Transaction {
private:
    int id;
    string date;
    double totalAmount;
    string paymentMethod;
    vector<TransactionItem> items;
public:
    Transaction(int id, const string& date, const string& paymentMethod);
    void addItem(const TransactionItem& item);
    double calculateTotal();
    string generateReceipt() const;
    void cancel();

    int getId() const;
    string getDate() const;
    double getTotalAmount() const;
    string getPaymentMethod() const;
    const vector<TransactionItem>& getItems() const;
};