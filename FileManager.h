#pragma once
#include "Store.h"
#include <string>

class FileManager {
public:
    static void saveCategories(const Store& store, const string& filename);
    static void saveProducts(const Store& store, const string& filename);
    static void saveTransactions(const Store& store, const string& filename);
    static void loadCategories(Store& store, const string& filename);
    static void loadProducts(Store& store, const string& filename);
};