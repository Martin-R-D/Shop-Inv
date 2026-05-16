#pragma once
#include <string>
using namespace std;

class Person {
protected:
    string name;
    string email;
public:
    Person(const string& name, const string& email);
    virtual ~Person() = default;
    virtual string getInfo() const = 0;
    string getName() const;
    string getEmail() const;
};