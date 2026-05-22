#pragma once
#include "Store.h"
#include <string>

class ReportManager {
public:
    static void revenueByPeriod(const Store& store, const string& dateFilter);
    static void topSellingProducts(const Store& store, int topN);
    static void inventoryValue(const Store& store);
    static void transactionSummary(const Store& store);
};
