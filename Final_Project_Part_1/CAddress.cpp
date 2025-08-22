#include <iostream>
#include "CAddress.h"

// The initializer list sets `city` to `"Tel Aviv"` to match the default value defined in the header file.
CAddress::CAddress(int houseNumber, string street, string city)
    : houseNumber(0), street(""), city("Tel Aviv")
{
    UpdateAddress(city, street, houseNumber);
}

CAddress::CAddress(const CAddress& other)
    : houseNumber(0), street(""), city("Tel Aviv")
{
    UpdateAddress(other.city, other.street, other.houseNumber);
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

void CAddress::Print() const
{
    cout << street
        << " "
        << houseNumber
        << ", "
        << city << endl;
}
