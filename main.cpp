#include <iostream>
#include "Admin.h"
#include "Cashier.h"
#include "Supplier.h"
#include "PhysicalProduct.h"
#include "ServiceProduct.h"
#include "Category.h"
#include "PercentDiscount.h"
#include "Transaction.h"
#include "TransactionItem.h"
#include "Delivery.h"
using namespace std;

int main() {
    cout << "=== Shop Inventory & Cashier System ===" << endl;
    cout << "System initialized successfully." << endl;

    Admin admin("Ivan", "ivan@shop.bg", 1);
    Cashier cashier("Maria", "maria@shop.bg", "morning");
    Supplier supplier("Petar", "petar@supplier.bg", "FoodCo");

    cout << admin.getInfo() << endl;
    cout << cashier.getInfo() << endl;
    cout << supplier.getInfo() << endl;

    return 0;
}