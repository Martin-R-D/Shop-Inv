#pragma once
#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;
    string barcode;
    int categoryId;
public:
    Product(int id, const string& name, double price, const string& barcode, int categoryId);
    virtual ~Product() = default;
    virtual string getDetails() const = 0;
    virtual string getType() const = 0;

    int getId() const;
    string getName() const;
    double getPrice() const;
    string getBarcode() const;
    int getCategoryId() const;
    void setName(const string& n);
    void setPrice(double p);
    void setBarcode(const string& b);
    void setCategoryId(int cId);
};