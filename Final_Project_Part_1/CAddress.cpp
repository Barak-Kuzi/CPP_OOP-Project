#include <iostream>
#include "CAddress.h"

// The initializer list sets `city` to `"Tel Aviv"` to match the default value defined in the header file.
CAddress::CAddress(int houseNumber, string street, string city)
    : houseNumber(0), street(""), city("Tel Aviv")
{
    UpdateAddress(city, street, houseNumber);
}

string CAddress::ConvertCharPtrToString(const char* str) {
    return (str ? string(str) : string(""));
}

CAddress::CAddress(int houseNumber, const char* street, const char* city)
    : houseNumber(houseNumber),
    street(ConvertCharPtrToString(street)),
    city(ConvertCharPtrToString(city)) 
{
    UpdateAddress(ConvertCharPtrToString(city), ConvertCharPtrToString(street), houseNumber);
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
    // TODO: use getCurrentAddress
    out << address.street
        << " " 
        << address.houseNumber
        << "  "
        << address.city
        << endl;
    return out;
}

string CAddress::GetCurrentAddress() const
{
    return street + " " + to_string(houseNumber) + ", " + city;
}