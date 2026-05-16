#pragma once
#include "Product.h"

class ServiceProduct : public Product {
private:
    int duration;
public:
    ServiceProduct(int id, const string& name, double price, const string& barcode, int categoryId, int duration);
    string getDetails() const override;
    string getType() const override;
    int getDuration() const;
    void setDuration(int d);
};