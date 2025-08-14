#include "CAddress.h"

void CAddress::init(int houseNumber, string street, string city)
{
    this->city = city;
    this->street = street;
    this->houseNumber = (houseNumber > 0) ? houseNumber : 0;
}

CAddress::CAddress(int houseNumber, string street, string city)
{
    init(houseNumber, street, city);
}

CAddress::CAddress(const CAddress& other)
{
    init(other.houseNumber, other.street, other.city);
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
    this->city = city;
    this->street = street;
    this->houseNumber = houseNumber;
}

void CAddress::Print() const
{
    cout << street
        << " "
        << houseNumber
        << ", "
        << city << endl;
}
