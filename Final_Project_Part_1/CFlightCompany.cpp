#include <iostream>
#include <fstream>

#include "CFlightCompany.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"
#include "FlightCompException.h"
#include "PlaneCrewFactory.h"

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

void CFlightCompany::SetName(string name) noexcept(false)
{
    if (name.empty())
    {
        throw CCompStringException("Company name must not be empty");
    }
        
    this->companyName = name;
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
    CPlane* newPlane = plane.Clone();

    if (newPlane->getSerialNumber() <= 0)
    {
        newPlane->SetSerialNumber_ForLoad(CPlane::GetNextSerial());
    }
    planes[planeCount] = newPlane;
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

ostream& operator<<(ostream& os, const CFlightCompany& comp) noexcept(false)
{
    if (comp.companyName.empty())
    {
        throw CCompStringException("Company name is empty");
    }
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

CCrewMember* CFlightCompany::GetCrewMember(int index) const noexcept(false)
{
    if (index < 0 || index >= crewCount)
    {
        throw CCompLimitException(crewCount - 1, "CrewMember index");
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

CPlane& CFlightCompany::operator[](int index) noexcept(false)
{
    if (index < 0 || index >= planeCount)
    {
        throw CCompLimitException(planeCount - 1, "plane index of the CFlightCompany");
    }
    return *planes[index];
}

const CPlane& CFlightCompany::operator[](int index) const noexcept(false)
{
    if (index < 0 || index >= planeCount)
    {
        throw CCompLimitException(planeCount - 1, "plane index of the CFlightCompany");
    }
    return *planes[index];
}

void CFlightCompany::SaveToFile(const char* filename) const noexcept(false)
{
    ofstream out(filename);
    if (!out)
    {
        throw CCompFileException(filename, "open for write");
    }
        
    out << companyName << "\n";

    out << crewCount << "\n";
    for (int i = 0; i < crewCount; ++i)
    {
        const CCrewMember* c = crews[i];
        if (dynamic_cast<const CHost*>(c))
        {
            const CHost* h = (const CHost*)c;
            out << 0 << " " << h->getName() << " " << h->getAirTimeMinutes()
                << " " << (int)h->GetType() << "\n";
        }
        else
        {
            const CPilot* p = (const CPilot*)c;
            out << 1 << " " << p->getName() << " " << p->getAirTimeMinutes() << " ";
            const CAddress& a = p->getAddress();
            bool has = !a.getCity().empty();
            out << (has ? 1 : 0);
            if (has)
            {
                out << " " << a.getHouseNumber() << " " << a.getStreet() << " " << a.getCity();
            }
            out << " " << (p->IsCaptain() ? 1 : 0) << "\n";
        }
    }

    out << planeCount << "\n";

    int lastId = 0;
    for (int i = 0; i < planeCount; ++i)
    {
        if (planes[i] && planes[i]->getSerialNumber() > lastId)
        {
            lastId = planes[i]->getSerialNumber();
        }
    }

    for (int i = 0; i < planeCount; ++i)
    {
        const CPlane* pl = planes[i];
        if (auto cg = dynamic_cast<const CCargo*>(pl))
        {
            out << 1 << " " << pl->getSerialNumber() << " " << pl->getModelName()
                << " " << pl->getSeatsNumber() << "\n";
            out << cg->GetMaxVol() << " " << cg->GetMaxKg()
                << " " << cg->GetCurrVol() << " " << cg->GetCurrKg() << "\n";
        }
        else
        {
            out << 0 << " " << lastId << " " << pl->getSerialNumber() << " "
                << pl->getModelName() << " " << pl->getSeatsNumber() << "\n";
        }
    }

    out << flightCount << "\n";
    for (int i = 0; i < flightCount; ++i)
    {
        const CFlight* f = flights[i];
        const CFlightInfo& fi = f->GetFlightInfo();

        const CPlane* fp = f->GetPlanePtr();
        if (fp)
        {
            out << fi.getDestination() << " " << fi.GetFNum() << " " << fi.getFlightTimeMinutes()
                << " " << fi.getFlightDistanceKm() << " 1 " << fp->getSerialNumber() << "\n";
        }
        else
        {
            out << fi.getDestination() << " " << fi.GetFNum() << " " << fi.getFlightTimeMinutes()
                << " " << fi.getFlightDistanceKm() << " 0 0\n";
        }

        int cnt = f->getCrewMembersCount();
        out << cnt << "\n";
        for (int j = 0; j < cnt; ++j)
        {
            const CCrewMember* c = f->GetCrewMemberAt(j);
            if (dynamic_cast<const CHost*>(c))
            {
                const CHost* h = (const CHost*)c;
                out << 0 << " " << h->getName() << " " << h->getAirTimeMinutes()
                    << " " << (int)h->GetType() << "\n";
            }
            else
            {
                const CPilot* p = (const CPilot*)c;
                out << 1 << " " << p->getName() << " " << p->getAirTimeMinutes() << " ";
                const CAddress& a = p->getAddress();
                bool has = !a.getCity().empty();
                out << (has ? 1 : 0);
                if (has)
                {
                    out << " " << a.getHouseNumber() << " " << a.getStreet() << " " << a.getCity();
                }  
                out << " " << (p->IsCaptain() ? 1 : 0) << "\n";
            }
        }
    }
}

const int CFlightCompany::GetCrewCount() const
{
    return this->crewCount;
}

CFlightCompany::CFlightCompany(const char* filename, int) noexcept(false)
    : CFlightCompany(string(filename))
{
    ifstream in(filename);
    if (!in)
    {
        throw CCompFileException(filename, "open for read");
    }

    in >> companyName;

    int crewC = 0;
    in >> crewC;
    for (int i = 0; i < crewC; ++i)
    {
        try
        {
            CCrewMember* c = CPlaneCrewFactory::GetCrewMemberFromFile(in);
            if (c)
            {
                try 
                { 
                    this->AddCrewMember(*c);
                }
                catch (const CFlightCompException& e)
                { 
                    e.Show();
                }
                delete c;
            }
        }
        catch (const CFlightCompException& e)
        {
            e.Show();
        }
    }

    int planeC = 0;
    in >> planeC;
    for (int i = 0; i < planeC; ++i)
    {
        try
        {
            CPlane* p = CPlaneCrewFactory::GetPlaneFromFile(in);
            if (p)
            {
                try 
                { 
                    this->AddPlane(*p);
                }
                catch (const CFlightCompException& e) 
                { 
                    e.Show();
                }
                delete p;
            }
        }
        catch (const CFlightCompException& e)
        {
            e.Show();
        }
    }

    int flightC = 0;
    in >> flightC;
    for (int i = 0; i < flightC; ++i)
    {
        try
        {
            string dest; 
            int num = 0, minutes = 0, km = 0;
            int hasPlane = 0;

            in >> dest >> num >> minutes >> km >> hasPlane;

            CFlightInfo fi(dest, num, minutes, km);
            CFlight* fl = new CFlight(fi);

            if (hasPlane)
            {
                int pid = 0;
                in >> pid;

                CPlane* use = nullptr;
                for (int k = 0; k < planeCount; ++k)
                {
                    if (planes[k] && planes[k]->getSerialNumber() == pid)
                    {
                        use = planes[k];
                        break;
                    }
                }
                if (!use)
                {
                    delete fl;
                    throw CCompStringException("Plane id in flight not found");
                }
                fl->SetPlane(use);
            }
            else
            {
                if (in.peek() == ' ' || in.peek() == '\t')
                {
                    int dummy;
                    if (in >> dummy) 
                    { 
                    }
                }
            }

            int fCrew = 0;
            in >> fCrew;
            for (int j = 0; j < fCrew; ++j)
            {
                try
                {
                    CCrewMember* temp = CPlaneCrewFactory::GetCrewMemberFromFile(in);
                    if (!temp)
                    {
                        continue;
                    }

                    CCrewMember* toAttach = nullptr;
                    const bool tempIsPilot = (dynamic_cast<CPilot*>(temp) != nullptr);
                    const string tempName = temp->getName();

                    for (int k = 0; k < crewCount && !toAttach; ++k)
                    {
                        if (!crews[k])
                        {
                            continue;
                        }
                        const bool sameType = (tempIsPilot == (dynamic_cast<CPilot*>(crews[k]) != nullptr));
                        if (sameType && crews[k]->getName() == tempName)
                        {
                            toAttach = crews[k];
                        }
                    }

                    if (!toAttach)
                    {
                        try 
                        { 
                            this->AddCrewMember(*temp);
                        }
                        catch (const CFlightCompException& e)
                        { 
                            e.Show();
                        }
                        for (int k = 0; k < crewCount && !toAttach; ++k)
                        {
                            if (!crews[k])
                            {
                                continue;
                            }
                            const bool sameType = (tempIsPilot == (dynamic_cast<CPilot*>(crews[k]) != nullptr));
                            if (sameType && crews[k]->getName() == tempName)
                            {
                                toAttach = crews[k];
                            }
                        }
                    }

                    if (toAttach)
                    {
                        *fl = *fl + toAttach;
                    }

                    delete temp;
                }
                catch (const CFlightCompException& e)
                {
                    e.Show();
                }
            }

            try 
            { 
                this->AddFlight(*fl);
            }
            catch (const CFlightCompException& e) 
            { 
                e.Show();
            }

            delete fl;
        }
        catch (const CFlightCompException& e)
        {
            e.Show();
        }
    }
}