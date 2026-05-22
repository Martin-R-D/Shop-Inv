#pragma once
#include "Store.h"
#include <string>

class HtmlReport {
private:
    static string htmlHeader(const string& title);
    static string htmlFooter();
    static string styleBlock();
public:
    static void generateProductReport(const Store& store, const string& filename);
    static void generateFullReport(const Store& store, const string& filename);
};
