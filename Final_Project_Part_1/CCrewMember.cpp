#include <iostream>
#include "CCrewMember.h"

using namespace std;

CCrewMember::CCrewMember(string name, CAddress address, int airTimeMinutes)
    : name(!name.empty() ? name : ""),
    address(address),
    airTimeMinutes((airTimeMinutes > 0) ? airTimeMinutes : 0)
{
}

CCrewMember::CCrewMember(const CCrewMember& other)
    : name(other.name), address(other.address), airTimeMinutes(other.airTimeMinutes)
{
}

CCrewMember::~CCrewMember()
{
}

bool CCrewMember::UpdateMinutes(int minutes)
{
    if (minutes > 0)
    {
        airTimeMinutes += minutes;
        return true;
    }
    return false;
}

string CCrewMember::getName() const
{
    return name;
}

CAddress CCrewMember::getAddress() const
{
    return address;
}

int CCrewMember::getAirTimeMinutes() const
{
    return airTimeMinutes;
}

void CCrewMember::setName(string name)
{
    this->name = !name.empty() ? name : "";
}

void CCrewMember::setAddress(CAddress address)
{
    this->address = address;
}

bool CCrewMember::IsEqual(const CCrewMember& other) const
{
    return this->name == other.name;
}

void CCrewMember::Print() const
{
    cout << "Crewmember "
        << name
        << " minutes "
        << airTimeMinutes << endl;
}
