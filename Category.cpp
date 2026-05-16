#include "Category.h"

Category::Category(int id, const string& name) : id(id), name(name) {}
int Category::getId() const { return id; }
string Category::getName() const { return name; }
void Category::setName(const string& n) { name = n; }