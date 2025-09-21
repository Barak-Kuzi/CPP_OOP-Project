#include "Host.h"

CHost::CHost(const string& name, HostType t, CAddress* address, int minutes)
    : CCrewMember(name, minutes, *address), type(t)
{
}

CHost::HostType CHost::GetType() const 
{ 
    return type; 
}

void CHost::SetType(HostType type) 
{ 
    type = type;
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
