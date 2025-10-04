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

static string readWord(ifstream& in) noexcept(false)
{
    string s;
    if (!(in >> s))
    {
        throw CCompFileException("Delta.txt", "read");
    }
    return s;
}

CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(ifstream& inFile) noexcept(false)
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

CPlane* CPlaneCrewFactory::GetPlaneFromFile(ifstream& inFile) noexcept(false)
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
    int x;
    while (true)
    {
        cout << prompt << ' ' << flush;
        if (cin >> x)
        {
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter an integer." << endl;
    }
}

string CPlaneCrewFactory::askStr(const char* prompt)
{
    string s;
    cout << prompt;
    while (true)
    {
        if (cin >> s)
        {
            return s;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a string: ";
    }
}

CPlane* CPlaneCrewFactory::GetPlaneFromUser() noexcept(false)
{
    int t;
    do
    {
        t = askInt("Plane type (0=Regular,1=Cargo): ");
    } while (t != 0 && t != 1);

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

CCrewMember* CPlaneCrewFactory::GetCrewFromUser() noexcept(false)
{
    int t;
    do
    {
        t = askInt("Crew type (0=Host,1=Pilot): ");
    } while (t != 0 && t != 1);

    string name = askStr("Name: ");
    int minutes = askInt("Air minutes: ");

    if (t == 0) 
    {
        int ht;
        do 
        { 
            ht = askInt("Host type (0=Regular,1=Super,2=Calcelan): ");
        } while (ht < 0 || ht > 2);

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
        int hasAddr;
        do 
        { 
            hasAddr = askInt("Has address? (0=No,1=Yes): ");
        } while (hasAddr != 0 && hasAddr != 1);

        CAddress addr(0, "", "Tel Aviv");
        const CAddress* pAddr = nullptr;

        if (hasAddr)
        {
            int house; 
            string street;
            string city;
            cout << "Enter house (int) street (string) city (string): ";

            while (!(cin >> house >> street >> city))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.";
            }

            addr = CAddress(house, street.c_str(), city.c_str());
            pAddr = &addr;
        }

        int cap;
        do 
        { 
            cap = askInt("Is captain? (0=No,1=Yes): ");
        } while (cap != 0 && cap != 1);

        return new CPilot(name, cap != 0, pAddr, minutes);
    }
    throw CCompStringException("Unknown crew type");
}

void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp)
{
    int p;
    do
    {
        p = askInt("Add plane (0=No,1=Yes)? ");
    } while (p != 0 && p != 1);

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
        if (lastId > 0 && lastId + 1 > CPlane::GetNextSerial())
        {
            CPlane::SetNextSerial(lastId + 1);
        }

        CPlane* pl = GetPlaneFromUser();
        if (pl)
        {
            comp.AddPlane(*pl);
            delete pl;
        }
    }

    int c;
    do
    {
        c = askInt("Add crew (0=No,1=Yes)? ");
    } while (c != 0 && c != 1);

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