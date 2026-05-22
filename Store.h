#pragma once
#include "Category.h"
#include "Product.h"
#include "PhysicalProduct.h"
#include "ServiceProduct.h"
#include "Transaction.h"
#include "TransactionItem.h"
#include "Supplier.h"
#include "Delivery.h"
#include <vector>
#include <string>
using namespace std;

class Store {
private:
    vector<Category*> categories;
    vector<Product*> products;
    vector<Transaction*> transactions;
    vector<Supplier*> suppliers;
    vector<Delivery*> deliveries;
    int nextTransactionId;
    int nextCategoryId;
    int nextProductId;
    int nextSupplierId;
    int nextDeliveryId;
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


    Transaction* createTransaction(const string& paymentMethod);
    void addItemToTransaction(Transaction* t, int productId, int qty);
    void finalizeTransaction(Transaction* t);
    void listTransactions() const;


    void applyDiscountToTransaction(Transaction* t, int itemIndex, Discount* d);
    vector<Transaction*> filterTransactionsByDate(const string& date) const;
    const vector<Transaction*>& getTransactions() const;

    void addSupplier(const string& name, const string& email, const string& company);
    void listSuppliers() const;
    Supplier* findSupplier(int index) const;
    void createDelivery(int supplierIndex);
    void receiveDelivery(int deliveryId);
    void listDeliveries() const;
    const vector<Supplier*>& getSuppliers() const;
    const vector<Delivery*>& getDeliveries() const;
};