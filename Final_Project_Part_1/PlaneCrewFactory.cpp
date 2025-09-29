#include <iostream>
#include <fstream>
#include <string>
#include "PlaneCrewFactory.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"
#include "FlightCompException.h"
#include "CFlightCompany.h"
using namespace std;

static string readWord(ifstream& in) 
{
    string s;
    if (!(in >> s))
    {
        throw CCompFileException("Delta.txt", "read");
    }
    return s;
}

CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(ifstream& inFile)
{
    int type;
    if (!(inFile >> type))
    {
        throw CCompFileException("Delta.txt", "read crew type");
    }

    if (type == 0)
    { 
        string name;
        int minutes;
        int t;
        inFile >> name >> minutes >> t;
        CHost::HostType hostType = CHost::eRegular;
        if (t == 1)
        {
            hostType = CHost::eSuper;
        }
        else if (t == 2)
        {
            hostType = CHost::eCalcelan;
        }
        return new CHost(name, hostType, CAddress(0, "", "Tel Aviv"), minutes);
    }
    else if (type == 1)
    {
        string name;
        int minutes;
        int hasAddr;
        inFile >> name >> minutes >> hasAddr;

        CAddress addr(0, "", "Tel Aviv");
        const CAddress* pAddr = nullptr;

        if (hasAddr)
        {
            int house; string street, city;
            inFile >> house >> street >> city;
            addr = CAddress(house, street.c_str(), city.c_str());
            pAddr = &addr;
        }

        int isCap; 
        inFile >> isCap;

        return new CPilot(name, isCap != 0, pAddr, minutes);
    }
    throw CCompStringException("Unknown crew type in file");
}

CPlane* CPlaneCrewFactory::GetPlaneFromFile(ifstream& inFile)
{
    int type;
    if (!(inFile >> type))
        throw CCompFileException("Delta.txt", "read plane type");

    if (type == 0) 
    {
        int lastID, id, seats; string model;
        inFile >> lastID >> id >> model >> seats;

        if (lastID + 1 > CPlane::GetNextSerial())
            CPlane::SetNextSerial(lastID + 1);

        CPlane* p = new CPlane(seats, model);
        p->SetSerialNumber_ForLoad(id);
        return p;
    }
    else if (type == 1) 
    {
        int id, seats; string model;
        inFile >> id >> model >> seats;

        float maxVol, maxKg, vol, kg;
        inFile >> maxVol >> maxKg >> vol >> kg;

        CCargo* c = new CCargo(seats, model, maxKg, maxVol);
        c->SetCurrVol(vol);
        c->SetCurrKg(kg);

        c->SetSerialNumber_ForLoad(id);
        return c;
    }

    throw CCompStringException("Unknown plane type in file");
}


PlaneType CPlaneCrewFactory::GetPlaneType(const CPlane* pPlane)
{
    return (dynamic_cast<const CCargo*>(pPlane)) ? eCargo : eRegular;
}

CrewType CPlaneCrewFactory::GetCrewType(const CCrewMember* pCrew)
{
    return (dynamic_cast<const CPilot*>(pCrew)) ? ePilot : eHost;
}

int CPlaneCrewFactory::askInt(const char* prompt)
{
    cout << prompt << ' ' << flush;
    int x; 
    cin >> x;
    return x;
}

string CPlaneCrewFactory::askStr(const char* prompt)
{ 
    cout << prompt;
    string s;
    cin >> s;
    return s;
}

CPlane* CPlaneCrewFactory::GetPlaneFromUser()
{
    cout << "Plane type (0=Regular,1=Cargo): ";
    int t; cin >> t;
    string model = askStr("Model: ");
    int seats = askInt("Seats: ");

    if (t == 0)
    {
        return new CPlane(seats, model);
    }
    if (t == 1) {
        int maxKg = askInt("Max KG: ");
        int maxVol = askInt("Max Volume: ");
        return new CCargo(seats, model, static_cast<float>(maxKg), static_cast<float>(maxVol));
    }
    throw CCompStringException("Unknown plane type");
}

CCrewMember* CPlaneCrewFactory::GetCrewFromUser()
{
    cout << "Crew type (0=Host,1=Pilot): " << flush;
    int t; 
    cin >> t;
    string name = askStr("Name: ");
    int minutes = askInt("Air minutes: ");

    if (t == 0) 
    {
        cout << "Host type (0=Regular,1=Super,2=Calcelan): ";
        int ht; cin >> ht;
        CHost::HostType e = CHost::eRegular;
        if (ht == 1)
        {
            e = CHost::eSuper;
        }
        else if (ht == 2)
        {
            e = CHost::eCalcelan;
        }
        CAddress addr(0, "", "Tel Aviv");
        return new CHost(name, e, addr, minutes);
    }
    else if (t == 1) 
    {
        cout << "Has address? (0/1): ";
        int has; 
        cin >> has;

        CAddress addr(0, "", "Tel Aviv");
        const CAddress* pAddr = nullptr;

        if (has) 
        {
            int house; 
            string street;
            string city;
            cout << "house street city: ";
            cin >> house >> street >> city;
            addr = CAddress(house, street.c_str(), city.c_str());
            pAddr = &addr;
        }

        cout << "Is captain? (0/1): ";
        int cap; cin >> cap;
        return new CPilot(name, cap != 0, pAddr, minutes);
    }
    throw CCompStringException("Unknown crew type");
}

void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp)
{
    cout << "Add plane (0/1)? " << flush;
    int p;
    cin >> p;

    if (p)
    {
        int lastId = 0;
        for (int i = 0; ; ++i)
        {
            try
            {
                const CPlane& plI = comp[i];
                if (plI.getSerialNumber() > lastId)
                {
                    lastId = plI.getSerialNumber();
                }
            }
            catch (const CFlightCompException&)
            {
                break;
            }
        }
        CPlane::SetNextSerial(lastId + 1);

        CPlane* pl = GetPlaneFromUser();
        if (pl)
        {
            comp.AddPlane(*pl);
            delete pl;
        }
    }

    cout << "Add crew (0/1)? " << flush;
    int c;
    cin >> c;

    if (c)
    {
        CCrewMember* cr = GetCrewFromUser();
        if (cr)
        {
            comp.AddCrewMember(*cr);
            delete cr;
        }
    }
}