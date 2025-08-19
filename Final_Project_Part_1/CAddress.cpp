#include "CAddress.h"

CAddress::CAddress(int houseNumber, string street, string city)
{
    UpdateAddress(city, street, houseNumber);
}

CAddress::CAddress(const CAddress& other)
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
    
    this->houseNumber = (houseNumber > 0) ? houseNumber : 0;
}

void CAddress::Print() const
{
    cout << street
        << " "
        << houseNumber
        << ", "
        << city << endl;
}
