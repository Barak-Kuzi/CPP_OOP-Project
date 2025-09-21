#include "Pilot.h"

CPilot::CPilot(const string& name, bool captain, CAddress* address, int minutes)
    : CCrewMember(name, minutes, address ? *address : CAddress(0, "", "Tel Aviv")),
    isCaptain(captain)
{
}

bool CPilot::IsCaptain() const 
{ 
    return isCaptain;
}

void CPilot::SetCaptain(bool captainStatus) 
{
    isCaptain = captainStatus; 
}

bool CPilot::Equals(const CCrewMember& other) const
{
    const CPilot* p = dynamic_cast<const CPilot*>(&other);
    if (!p)
    {
        return CCrewMember::Equals(other);
    }
    return (getName() == p->getName()) && (getAddress() == p->getAddress());
}

void CPilot::OnUniform(ostream& out) const
{

    out << getName() << ": this is the fifth time I get a new uniform, this is a waste of money!" << endl;
}

int CPilot::addMinutesByRole(int baseMinutes) const
{
    int add = baseMinutes;
    if (isCaptain)
    {
        double bonus = add * 0.1;
        add += static_cast<int>(bonus);
        return add;
    }
    return add;
}

void CPilot::OnGift(ostream& out) const
{
    out << getName() << " thanking the company for receiving the holiday gift" << endl;
}

void CPilot::OnSimulator(ostream& out) const
{
    out << "Pilot " << getName() << " got the message will come soon" << endl;
}

void CPilot::Print(ostream& out) const
{
    out << "Pilot  " << getName()
        << " minutes " << getAirTimeMinutes();

    const CAddress addr = getAddress();
    if (addr.getHouseNumber() > 0 || !addr.getStreet().empty())
    {
        out << " Home " << addr;
    }
    out << (isCaptain ? "  a Captain" : " Not a Captain") << '\n';
}

CCrewMember* CPilot::Clone() const
{
    return new CPilot(*this);
}
