#pragma once

#include <iostream>
#include <string>
using namespace std;

class CAddress
{
private:
    string city;
    string street;
    int houseNumber;

public:
    CAddress(int houseNumber, string street, string city = "Tel Aviv");

    CAddress(const CAddress& other);

    ~CAddress();

    string getCity() const;
    string getStreet() const;
    int getHouseNumber() const;

    void UpdateAddress(string city, string street, int houseNumber);
    void Print() const;

};