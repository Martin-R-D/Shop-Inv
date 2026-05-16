#include "ServiceProduct.h"

ServiceProduct::ServiceProduct(int id, const string& name, double price, const string& barcode, int categoryId, int duration)
    : Product(id, name, price, barcode, categoryId), duration(duration) {}

string ServiceProduct::getDetails() const {
    return "[Service] " + name + " | Price: " + to_string(price) + " | Duration: " + to_string(duration) + " min";
}

string ServiceProduct::getType() const { return "service"; }
int ServiceProduct::getDuration() const { return duration; }
void ServiceProduct::setDuration(int d) { if (d > 0) duration = d; }