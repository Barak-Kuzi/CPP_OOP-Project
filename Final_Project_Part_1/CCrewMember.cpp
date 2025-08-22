#include <iostream>
#include "CCrewMember.h"

using namespace std;

// No default value is needed for `address` because its constructor already ensures a valid state.
CCrewMember::CCrewMember(string name, CAddress address, int airTimeMinutes)
    : name(""), address(address), airTimeMinutes(0)
{
    setName(name);
    UpdateMinutes(airTimeMinutes);
}

CCrewMember::CCrewMember(const CCrewMember& other)
    : name(""), address(other.address), airTimeMinutes(0)
{
    setName(other.name);
    UpdateMinutes(other.airTimeMinutes);
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
    if (!name.empty()) 
    {
        this->name = name;
    }
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
