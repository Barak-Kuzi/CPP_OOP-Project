#include <iostream>
#include "CCrewMember.h"

using namespace std;

int CCrewMember::nextID = CCrewMember::START_ID;

void CCrewMember::init(string name, int airTimeMinutes, CAddress address)
{
    setName(name);
    setAddress(address);
    UpdateMinutes(airTimeMinutes);
}

CCrewMember::CCrewMember(string name,  int airTimeMinutes, CAddress address)
    : name(""), address(CAddress(0, "", "Tel Aviv")), airTimeMinutes(0), memberID(nextID++)
{
    init(name, airTimeMinutes, address);
}

CCrewMember::CCrewMember(const CCrewMember& other)
    : name(""), address(CAddress(0, "", "Tel Aviv")), airTimeMinutes(0), memberID(other.memberID)
{
    *this = other;
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

// The constructor already ensures a valid state.
void CCrewMember::setAddress(CAddress address)
{
    this->address = address;
}

void CCrewMember::Print() const
{
    cout << "Crewmember "
        << name
        << " minutes "
        << airTimeMinutes << endl;
}

int CCrewMember::getMemberID() const
{
    return this->memberID;
}

CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
    if (this != &other)
    {
        init(other.name, other.airTimeMinutes, other.address);    
    }
    return *this;
}

bool CCrewMember::operator+=(int minutes)
{
    if (minutes > 0)
    {
        airTimeMinutes += minutes;
        return true;
    }
        
    return false;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
    return this->memberID == other.memberID;
}

ostream& operator<<(ostream& out, const CCrewMember& crewMember)
{
    out << "Crewmember " << crewMember.name
        << " minutes "
        << crewMember.airTimeMinutes << endl;
    return out;
}