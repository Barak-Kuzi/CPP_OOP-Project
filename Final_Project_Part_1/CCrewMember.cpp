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

int CCrewMember::addMinutesByRole(int baseMinutes) const
{
    return baseMinutes;
}

CCrewMember::CCrewMember(string name,  int airTimeMinutes, CAddress address)
    : name(""), address(CAddress(0, "", "Tel Aviv")), airTimeMinutes(0), memberID(nextID++)
{
    init(name, airTimeMinutes, address);
}

CCrewMember::CCrewMember(const CCrewMember& other)
    : name(""), address(CAddress(0, "", "Tel Aviv")), airTimeMinutes(0), memberID(nextID++)
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

const string& CCrewMember::getName() const
{
    return name;
}

const CAddress& CCrewMember::getAddress() const
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

int CCrewMember::getMemberID() const
{
    return this->memberID;
}

CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
    if (this != &other)
    {
        init(other.name, other.airTimeMinutes, other.address);
        this->memberID = other.memberID;
    }
    return *this;
}

bool CCrewMember::operator+=(int minutes)
{
    if (minutes > 0)
    {
        int add = addMinutesByRole(minutes);
        UpdateMinutes(add);
        return true;
    }
        
    return false;
}

ostream& operator<<(ostream& out, const CCrewMember& crewMember)
{
    crewMember.Print(out);
    return out;
}

void CCrewMember::OnGift(ostream& out) const
{
    out << "Thank you!" << endl;
}

bool CCrewMember::Equals(const CCrewMember& other) const
{
    return name == other.name;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
    return Equals(other);
}
bool CCrewMember::operator!=(const CCrewMember& other) const
{
    return !Equals(other);
}