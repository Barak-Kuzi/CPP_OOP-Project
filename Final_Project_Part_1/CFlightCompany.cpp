#include <iostream>
#include "CFlightCompany.h"

using namespace std;


void CFlightCompany::initFlightCompanyArrays()
{
    for (int i = 0; i < MAX_CREWS; i++)
    {
        crews[i] = nullptr;
    }

    for (int i = 0; i < MAX_PLANES; i++)
    {
        planes[i] = nullptr;
    }

    for (int i = 0; i < MAX_FLIGHTS; i++)
    {
        flights[i] = nullptr;
    }
}

CFlightCompany::CFlightCompany(string companyName) 
    : companyName(""), crewCount(0), planeCount(0), flightCount(0)
{
    initFlightCompanyArrays();
    SetName(companyName);
}

CFlightCompany::~CFlightCompany()
{
    initFlightCompanyArrays();
}

string CFlightCompany::getCompanyName() const
{
    return companyName;
}

void CFlightCompany::SetName(string name)
{
    if (!name.empty())
    {
        this->companyName = name;
    }
}

void CFlightCompany::Print(ostream& out) const
{
    cout << *this;
}

bool CFlightCompany::AddCrewMember(const CCrewMember& crew) {
    if (crewCount >= MAX_CREWS)
    {
        return false;
    }

    for (int i = 0; i < crewCount; i++) 
    {   
        if (*crews[i] == crew)
        {
            return false;
        }
    }

    crews[crewCount] = new CCrewMember(crew);
    crewCount++;

    return true;
}

bool CFlightCompany::AddPlane(const CPlane& plane) {
    if (planeCount >= MAX_PLANES)
    {
        return false;
    }

    for (int i = 0; i < planeCount; i++) 
    {
        if (*planes[i] == plane)
        {
            return false;
        }
    }

    planes[planeCount] = new CPlane(plane);
    planeCount++;
    
    return true;
}

bool CFlightCompany::AddFlight(const CFlight& flight) {
    if (flightCount >= MAX_FLIGHTS)
    {
        return false;
    }

    for (int i = 0; i < flightCount; i++)
    {
        if (*flights[i] == flight)
        {
            return false;
        }
    }

    flights[flightCount] = new CFlight(flight);
    flightCount++;

    return true;
}

CCrewMember* CFlightCompany::getCrewMemberById(int id) {
    for (int i = 0; i < crewCount; i++) {
        if (crews[i]->getMemberID() == id)
        {
            return crews[i];
        }
    }
    return nullptr;
}

CFlight* CFlightCompany::getFlightByNumber(int flightNum) {
    for (int i = 0; i < flightCount; i++) 
    {
        if (flights[i]->getFlightInfo().GetFNum() == flightNum)
        {
            return flights[i];
        }
    }
    return nullptr;
}

bool CFlightCompany::AddCrewToFlight(int flightNum, int crewMemberId) {
    CCrewMember* crewMember = getCrewMemberById(crewMemberId);
    CFlight* flight = getFlightByNumber(flightNum);

    if (!crewMember || !flight)
    {
        return false;
    }

    (*flight) + (*crewMember);
    
    return true;
}

CPlane* CFlightCompany::GetPlane(int idx) {
    if (idx < 0 || idx >= planeCount)
    {
        return nullptr;
    }

    return planes[idx];
}

void CFlightCompany::PrintCrewMembers() const
{
    cout << "There are " << crewCount << " Crew members:" << endl;
    if (crewCount > 0)
    {
        for (int i = 0; i < crewCount; i++)
        {
            if (crews[i] != nullptr)
            {
                crews[i]->Print();
            }
        }
    }
}

void CFlightCompany::PrintPlanes() const
{
    cout << "There are " << planeCount << " Planes:" << endl;
    if (planeCount > 0)
    {
        for (int i = 0; i < planeCount; i++)
        {
            if (planes[i] != nullptr)
            {
                planes[i]->Print();
            }
        }
    }
}

void CFlightCompany::PrintFlights() const
{
    cout << "There are " << flightCount << " Flights:" << endl;
    if (flightCount > 0)
    {
        for (int i = 0; i < flightCount; i++)
        {
            cout << *flights[i];
        }
    }
}

ostream& operator<<(ostream& os, const CFlightCompany& comp) {
    os << "Flight company: " << comp.companyName << endl;

    os << "There are " << comp.crewCount << " Crew members:" << endl;
    for (int i = 0; i < comp.crewCount; i++) 
    {
        if (comp.crews[i])
        {
            os << *comp.crews[i];
        }
    }

    os << "There are " << comp.planeCount << " Planes:" << endl;
    for (int i = 0; i < comp.planeCount; i++) 
    {
        if (comp.planes[i])
        {
            os << *comp.planes[i];
        }
    }

    os << "There are " << comp.flightCount << " Flights:" << endl;
    for (int i = 0; i < comp.flightCount; i++)
    {
        if (comp.flights[i])
        {
            os << *comp.flights[i];
        }
    }

    return os;
}

