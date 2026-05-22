#include "ReportManager.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

void ReportManager::revenueByPeriod(const Store& store, const string& dateFilter) {
    double total = 0;
    int count = 0;
    for (const auto* t : store.getTransactions()) {
        if (dateFilter.empty() || t->getDate().find(dateFilter) != string::npos) {
            total += t->getTotalAmount();
            count++;
        }
    }
    cout << "\n--- Revenue Report ---" << endl;
    cout << "  Filter: " << (dateFilter.empty() ? "All time" : dateFilter) << endl;
    cout << "  Transactions: " << count << endl;
    cout << fixed << setprecision(2);
    cout << "  Total revenue: " << total << endl;
}

void ReportManager::topSellingProducts(const Store& store, int topN) {
    map<int, int> soldCount;
    map<int, string> productNames;

    for (const auto* t : store.getTransactions()) {
        for (const auto& item : t->getItems()) {
            int pid = item.getProduct()->getId();
            soldCount[pid] += item.getQuantity();
            productNames[pid] = item.getProduct()->getName();
        }
    }

    vector<pair<int, int>> sorted(soldCount.begin(), soldCount.end());
    sort(sorted.begin(), sorted.end(),
        [](const pair<int,int>& a, const pair<int,int>& b) { return a.second > b.second; });

    cout << "\n--- Top " << topN << " Selling Products ---" << endl;
    int shown = 0;
    for (const auto& p : sorted) {
        if (shown >= topN) break;
        cout << "  " << productNames[p.first] << " — sold: " << p.second << endl;
        shown++;
    }
    if (shown == 0) cout << "  No sales data." << endl;
}

void ReportManager::inventoryValue(const Store& store) {
    double totalValue = 0;
    int lowStockCount = 0;
    cout << "\n--- Inventory Value Report ---" << endl;
    for (const auto* p : store.getProducts()) {
        const PhysicalProduct* pp = dynamic_cast<const PhysicalProduct*>(p);
        if (pp) {
            double val = pp->getQuantity() * pp->getPrice();
            totalValue += val;
            if (pp->isLowStock()) lowStockCount++;
            cout << "  " << pp->getName() << ": " << pp->getQuantity()
                 << " x " << pp->getPrice() << " = " << val << endl;
        }
    }
    cout << "  ---" << endl;
    cout << "  Total value: " << totalValue << endl;
    cout << "  Low stock items: " << lowStockCount << endl;
}

void ReportManager::transactionSummary(const Store& store) {
    int cashCount = 0, cardCount = 0;
    double cashTotal = 0, cardTotal = 0;
    for (const auto* t : store.getTransactions()) {
        if (t->getPaymentMethod() == "cash") { cashCount++; cashTotal += t->getTotalAmount(); }
        else { cardCount++; cardTotal += t->getTotalAmount(); }
    }
    cout << "\n--- Transaction Summary ---" << endl;
    cout << fixed << setprecision(2);
    cout << "  Cash: " << cashCount << " transactions, total: " << cashTotal << endl;
    cout << "  Card: " << cardCount << " transactions, total: " << cardTotal << endl;
    cout << "  Grand total: " << cashTotal + cardTotal << endl;
}
