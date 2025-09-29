#include "CFlight.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"
#include "FlightCompException.h"

void CFlight::initCrewMembersArr()
{
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = nullptr;
    }
}

CFlight::CFlight(const CFlightInfo& info, CPlane* plane) : 
    flightInfo(info), plane(nullptr), crewCount(0)
{
    initCrewMembersArr();
    SetPlane(plane);
}

CFlight::CFlight(const CFlight& other)
    : flightInfo(other.flightInfo), plane(other.plane), crewCount(other.crewCount)
{
    *this = other;
}

// The flight does not own the plane (it belongs to the company), so it must not be deleted here.
// A pointer is sent to the plane and it is not made 'new'.
CFlight::~CFlight()
{
    for (int i = 0; i < MAX_CREW; i++)
    {
        crewMembers[i] = nullptr;
    }
}

CFlight& CFlight::operator=(const CFlight& other)
{
    if (this != &other)
    {
        flightInfo = other.flightInfo;
        SetPlane(other.plane);
        crewCount = other.crewCount;
        for (int i = 0; i < MAX_CREW; i++)
        {
            if (other.crewMembers[i])
            {
                crewMembers[i] = other.crewMembers[i];
            }
            else
            {
                crewMembers[i] = nullptr;
            }
        }
    }
    return *this;
}

const CFlightInfo& CFlight::GetFlightInfo() const
{
    return this->flightInfo;
}

void CFlight::SetPlane(CPlane* newPlane)
{
    if (newPlane != nullptr)
    {
        plane = newPlane;
    }
}

const CPlane CFlight::getPlane() const
{
    return *this->plane;
}

const CCrewMember* CFlight::getCrewMember() const
{
    return *this->crewMembers;
}

const int CFlight::getCrewMembersCount() const
{
    return this->crewCount;
}

CFlight& operator+(CFlight& f, const CCrewMember& crew) {
    if (f.crewCount < MAX_CREW)
    {
        for (int i = 0; i < f.crewCount; i++)
        {
            if (!f.crewMembers[i]->getName().compare(crew.getName()))
            {
                return f;
            }
        }
        f.crewMembers[f.crewCount] = const_cast<CCrewMember*>(&crew);
        f.crewCount++;
    }
    return f;

}

CFlight& operator+(CFlight& f, const CCrewMember* pCrew)
{
    if (!pCrew)
    {
        return f;
    }

    for (int i = 0; i < f.crewCount; ++i)
    {
        if (f.crewMembers[i] == pCrew)
        {
            return f;
        }
            
        if (*(f.crewMembers[i]) == *pCrew)
        {
            return f;
        }
    }

    if (f.crewCount < MAX_CREW)
        f.crewMembers[f.crewCount++] = const_cast<CCrewMember*>(pCrew);

    return f;
}

ostream& operator<<(ostream& out, const CFlight& flight)
{
    out << "Flight " << flight.flightInfo;

    if (flight.plane)
    {
        out << *flight.plane;
    }
    else
    {
        out << " No plane assign yet ";
    }

    out << " There are " << flight.crewCount << " crew memebers in flight:" << endl;
    for (int i = 0; i < flight.crewCount; i++)
    {
        if (flight.crewMembers[i])
        {
            out << *flight.crewMembers[i];
        }
    }

    return out;
}

bool CFlight::operator==(const CFlight& other) const
{
    return (flightInfo == other.flightInfo);
}

bool CFlight::TakeOff()
{
    if (!plane)
    {
        throw CCompStringException("No plane attached to flight");
    }

    int pilots = 0, superHosts = 0;
    for (int i = 0; i < crewCount; ++i)
    {
        if (!crewMembers[i])
        {
            continue;
        }

        if (dynamic_cast<CPilot*>(crewMembers[i]))
        {
            ++pilots;
        }

        if (auto* h = dynamic_cast<CHost*>(crewMembers[i]))
        {
            if (h->GetType() == CHost::eSuper)
            {
                ++superHosts;
            }
        }
            
    }

    bool isCargo = (dynamic_cast<CCargo*>(plane) != nullptr);

    if (isCargo)
    {
        if (pilots < 1)
        {
            throw CCompStringException("Illegal takeoff: cargo flight requires at least one pilot");
        }
    }
    else 
    {
        if (pilots != 1)
        {
            throw CCompStringException("Illegal takeoff: passenger flight must have exactly one pilot");
        }

        if (superHosts > 1)
        {
            throw CCompStringException("Illegal takeoff: at most one Super-Host is allowed");
        }
    }

    int minutes = flightInfo.getFlightTimeMinutes();
    for (int i = 0; i < crewCount; ++i)
    {
        if (crewMembers[i])
        {
            *(crewMembers[i]) += minutes;
        }
    }
    
    plane->OnTakeoff(minutes);
    return true;
}

CPlane* CFlight::GetPlanePtr()
{
    return plane;
}

const CPlane* CFlight::GetPlanePtr() const
{
    return plane;
}

const CCrewMember* CFlight::GetCrewMemberAt(int index) const
{
    if (index < 0 || index >= crewCount)
    {
        throw CCompLimitException(crewCount - 1, "flight crew index");
    }
        
    return crewMembers[index];
}