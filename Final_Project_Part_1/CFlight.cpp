#include "CFlight.h"

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
        delete crewMembers[i];
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

const CFlightInfo CFlight::getFlightInfo() const
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
            if (*f.crewMembers[i] == crew)
            {
                return f;
            }
        }
        f.crewMembers[f.crewCount] = new CCrewMember(crew);
        f.crewCount++;
    }
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
