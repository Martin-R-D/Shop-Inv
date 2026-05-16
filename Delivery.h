#pragma once
#include <string>
#include <vector>
using namespace std;

class Delivery {
private:
    int id;
    string deliveryDate;
    string status;
    int supplierId;
    vector<pair<int, int>> productQuantities;
public:
    Delivery(int id, const string& deliveryDate, int supplierId);
    void addProduct(int productId, int quantity);
    void receive();
    string getStatusStr() const;
    int getId() const;
    string getDeliveryDate() const;
    int getSupplierId() const;
    const vector<pair<int, int>>& getProductQuantities() const;
};