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

    this->city = !city.empty() ? city : "";

    this->street = !street.empty() ? street : "";

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
