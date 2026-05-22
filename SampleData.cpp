#include "SampleData.h"
#include <iostream>
#include <fstream>

void SampleData::seed(Store& store) {
    ifstream test("categories.txt");
    if (test.good()) { test.close(); return; }
    test.close();

    cout << "Seeding sample data..." << endl;

    store.addCategory("Drinks");
    store.addCategory("Food");
    store.addCategory("Services");

    store.addPhysicalProduct("Coca-Cola", 2.50, "100001", 1, 50, 10);
    store.addPhysicalProduct("Water 500ml", 1.00, "100002", 1, 100, 20);
    store.addPhysicalProduct("Bread", 1.20, "200001", 2, 30, 5);
    store.addPhysicalProduct("Cheese 200g", 3.80, "200002", 2, 15, 3);
    store.addPhysicalProduct("Chips", 2.00, "200003", 2, 40, 8);
    store.addServiceProduct("Home Delivery", 5.00, "300001", 3, 30);
    store.addServiceProduct("Gift Wrapping", 2.00, "300002", 3, 10);

    cout << "Sample data loaded." << endl;
}
