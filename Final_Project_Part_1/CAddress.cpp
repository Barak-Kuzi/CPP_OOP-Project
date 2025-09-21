#include <iostream>
#include "CAddress.h"

string CAddress::ConvertCharPtrToString(const char* str) {
    return (str ? string(str) : string(""));
}

// The initializer list sets `city` to `"Tel Aviv"` to match the default value defined in the header file.
// Without the char* to string conversion function, the main does not run,
// because you cannot send NULL to a constructor that accepts a string.
CAddress::CAddress(int houseNumber, const char* street, const char* city)
    : houseNumber(0),
    street(ConvertCharPtrToString(street)),
    city(ConvertCharPtrToString("Tel Aviv"))
{
    UpdateAddress(ConvertCharPtrToString(city), ConvertCharPtrToString(street), houseNumber);
}

CAddress::CAddress(const CAddress& other)
    : houseNumber(0), street(""), city("Tel Aviv")
{
    *this = other;
}

CAddress::~CAddress()
{
}

string CAddress::getCity() const
{
    return city;
}

string CAddress::getStreet() const
{
    return street;
}

int CAddress::getHouseNumber() const
{
    return houseNumber;
}

void CAddress::UpdateAddress(string city, string street, int houseNumber)
{
    if (!city.empty()) 
    {
        this->city = city;
    }

    if (!street.empty()) 
    {
        this->street = street;
    }

    if (houseNumber > 0) 
    {
        this->houseNumber = houseNumber;
    }
}

CAddress& CAddress::operator=(const CAddress& other)
{
    if (this != &other)
    {
        UpdateAddress(other.city, other.street, other.houseNumber);
    }
    return *this;
}

bool CAddress::operator==(const CAddress& other) const
{
    return (city == other.city &&
        street == other.street &&
        houseNumber == other.houseNumber);
}

bool CAddress::operator!=(const CAddress& other) const
{
    return !(*this == other);
}
    
istream& operator>>(istream& in, CAddress& address)
{
    cout << "Please enter house number street name and city name:" << endl;
    in >> address.houseNumber >> address.street >> address.city;
    return in;
}

ostream& operator<<(ostream& out, const CAddress& address)
{
    out << address.GetCurrentAddress();
    return out;
}

string CAddress::GetCurrentAddress() const
{
    return street + " " + to_string(houseNumber) + "  " + city + "\n";
}