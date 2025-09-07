#pragma once

#include <string>
using namespace std;

class CAddress
{
private:
    string city;
    string street;
    int houseNumber;

    static string ConvertCharPtrToString(const char* str);

public:
    CAddress() = delete;

    CAddress(int houseNumber, const char* street, const char* city = "Tel Aviv");

    CAddress(const CAddress& other);

    ~CAddress();

    string getCity() const;
    string getStreet() const;
    int getHouseNumber() const;
    string GetCurrentAddress() const;

    void UpdateAddress(string city, string street, int houseNumber);

    CAddress& operator=(const CAddress& other);

    bool operator==(const CAddress& other) const;

    bool operator!=(const CAddress& other) const;

    friend istream& operator>>(istream& in, CAddress& addr);

    friend ostream& operator<<(ostream& out, const CAddress& addr);
};