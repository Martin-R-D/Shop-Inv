#pragma once
#include <string>
using namespace std;

class Category {
private:
    int id;
    string name;
public:
    Category(int id, const string& name);
    int getId() const;
    string getName() const;
    void setName(const string& n);
};