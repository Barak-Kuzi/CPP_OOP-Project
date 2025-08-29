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

    CAddress(int houseNumber, string street, string city = "Tel Aviv");
    CAddress(int houseNumber, const char* street, const char* city);

    CAddress(const CAddress& other);

    ~CAddress();

    string getCity() const;
    string getStreet() const;
    int getHouseNumber() const;
    string GetCurrentAddress() const;

    void UpdateAddress(string city, string street, int houseNumber);
    void Print() const;

    // Operator =
    CAddress& operator=(const CAddress& other);

    // Operator ==
    bool operator==(const CAddress& other) const;

    // Operator !=
    bool operator!=(const CAddress& other) const;

    // Operator >>  (input)
    friend istream& operator>>(istream& in, CAddress& addr);

    // Operator <<  (output)
    friend ostream& operator<<(ostream& out, const CAddress& addr);
};