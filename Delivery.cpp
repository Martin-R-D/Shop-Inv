#include "Delivery.h"

Delivery::Delivery(int id, const string& deliveryDate, int supplierId)
    : id(id), deliveryDate(deliveryDate), status("pending"), supplierId(supplierId) {}

void Delivery::addProduct(int productId, int quantity) {
    productQuantities.push_back({productId, quantity});
}

void Delivery::receive() { status = "received"; }
string Delivery::getStatusStr() const { return status; }
int Delivery::getId() const { return id; }
string Delivery::getDeliveryDate() const { return deliveryDate; }
int Delivery::getSupplierId() const { return supplierId; }
const vector<pair<int, int>>& Delivery::getProductQuantities() const { return productQuantities; }