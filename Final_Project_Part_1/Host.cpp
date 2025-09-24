#include "Host.h"

void CHost::init(const string& name, HostType t, const CAddress& address, int minutes)
{
    CCrewMember::init(name, minutes, address);
    SetType(t);
}

bool CHost::isValidHostType(HostType t)
{
    return t == CHost::eRegular || t == CHost::eSuper || t == CHost::eCalcelan;
}

CHost::CHost(const string& name, HostType t, CAddress address, int minutes)
    : CCrewMember(name, minutes, address), type(t)
{
    init(name, t, address, minutes);
}

CHost::CHost(const CHost& other)
    : CCrewMember(other), type(other.type)
{
    SetType(other.type);
}

CHost& CHost::operator=(const CHost& other)
{
    if (this != &other)
    {
        CCrewMember::operator=(other);
        SetType(other.type);
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

void CHost::SetType(HostType t) 
{
    if (isValidHostType(t))
    {
        this->type = t;
    }
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
