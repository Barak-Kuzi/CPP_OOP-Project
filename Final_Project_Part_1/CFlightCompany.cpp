#include <iostream>
#include "CFlightCompany.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"

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
    for (int i = 0; i < MAX_CREWS; i++)
    {
        delete crews[i];
        crews[i] = nullptr;
    }

    for (int i = 0; i < MAX_PLANES; i++)
    {
        delete planes[i];
        planes[i] = nullptr;
    }

    for (int i = 0; i < MAX_FLIGHTS; i++)
    {
        delete flights[i];
        flights[i] = nullptr;
    }
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

    crews[crewCount] = crew.Clone();
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

    planes[planeCount] = plane.Clone();
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

CCrewMember* CFlightCompany::getCrewMemberByName(const string& name)
{
    for (int i = 0; i < crewCount; i++) {
        if (crews[i]->getName() == name)
        {
            return crews[i];
        }
    }
    return nullptr;
}

CFlight* CFlightCompany::GetFlightByNum(int flightNum) {
    for (int i = 0; i < flightCount; i++) 
    {
        if (flights[i]->GetFlightInfo().GetFNum() == flightNum)
        {
            return flights[i];
        }
    }
    return nullptr;
}

bool CFlightCompany::AddCrewToFlight(int flightNum, string name) {
    CCrewMember* crewMember = getCrewMemberByName(name);
    CFlight* flight = GetFlightByNum(flightNum);

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

CCrewMember* CFlightCompany::GetCrewMember(int index) const
{
    if (index < 0 || index >= crewCount)
    {
        return nullptr;
    }

    return crews[index];
}

int CFlightCompany::GetCargoCount() const
{
    int cnt = 0;
    for (int i = 0; i < planeCount; ++i)
    {
        if (dynamic_cast<CCargo*>(planes[i]))
        {
            ++cnt;
        }
    }
        
    return cnt;
}

void CFlightCompany::PilotsToSimulator()
{
    for (int i = 0; i < crewCount; ++i)
    {
        if (auto* p = dynamic_cast<CPilot*>(crews[i]))
        {
            p->OnSimulator(cout);
        }
    }
}

void CFlightCompany::CrewGetPresent()
{
    for (int i = 0; i < crewCount; ++i)
    {
        if (crews[i])
        {
            crews[i]->OnGift(cout);
        }
    }
}

void CFlightCompany::CrewGetUniform()
{
    for (int i = 0; i < crewCount; ++i)
    {
        if (crews[i])
        {
            crews[i]->OnUniform(cout);
        }
    }
}