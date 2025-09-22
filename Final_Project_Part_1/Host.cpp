#include "Host.h"

CHost::CHost(const string& name, HostType t, CAddress* address, int minutes)
    : CCrewMember(name, minutes, *address), type(t)
{
}

CHost::CHost(const CHost& other)
    : CCrewMember(other), type(other.type)
{
}

CHost& CHost::operator=(const CHost& other)
{
    if (this != &other)
    {
        CCrewMember::operator=(other);
        type = other.type;
    }
    return *this;
}

CHost::~CHost()
{
}

CHost::HostType CHost::GetType() const 
{ 
    return type; 
}

void CHost::SetType(HostType type) 
{ 
    this->type = type;
}

bool CHost::Equals(const CCrewMember& other) const
{
    return CCrewMember::Equals(other);
}

void CHost::OnUniform(ostream& out) const
{
    out << getName() << ": I think the new uniform is very nice!" << endl;
}

void CHost::OnGift(ostream& out) const
{
    out <<  getName() << " thanking the company for receiving the holiday gift" << endl << "I was not expecting it" << endl;
}

void CHost::Print(ostream& out) const
{
    const char* typeStr =
        (type == eRegular ? "Regular" :
            (type == eSuper ? "Super" : "Calaelan"));

    out << "Host " << typeStr << " " << getName()
        << " minutes " << CCrewMember::getAirTimeMinutes() << '\n';
}

CCrewMember* CHost::Clone() const
{
    return new CHost(*this);
}
