#pragma once

#include <string>
#include "CCrewMember.h"
#include "CPlane.h"
#include "CFlight.h"
using namespace std;


const int MAX_CREWS = 50;
const int MAX_PLANES = 20;
const int MAX_FLIGHTS = 100;

class CFlightCompany
{
private:
    string companyName;

    CCrewMember* crews[MAX_CREWS];
    int crewCount;

    CPlane* planes[MAX_PLANES];
    int planeCount;

    CFlight* flights[MAX_FLIGHTS];
    int flightCount;

    CCrewMember* getCrewMemberByName(const string& name);
    void initFlightCompanyArrays();

public:
    CFlightCompany() = delete;
    CFlightCompany(string companyName);

    CFlightCompany(const CFlightCompany& other) = delete;
    CFlightCompany& operator=(const CFlightCompany& other) = delete;

    ~CFlightCompany();

    string getCompanyName() const;

    void SetName(string name) noexcept(false);

    void Print(ostream& out) const;

    bool AddCrewMember(const CCrewMember& crew);

    bool AddPlane(const CPlane& plane);

    bool AddFlight(const CFlight& flight);

    bool AddCrewToFlight(int flightNum, string name);

    CPlane* GetPlane(int index);

    friend ostream& operator<<(ostream& out, const CFlightCompany& company) noexcept(false);

    CFlight* GetFlightByNum(int flightNumber);

    CCrewMember* GetCrewMember(int index) const noexcept(false);

    int GetCargoCount() const;

    void PilotsToSimulator();

    void CrewGetPresent();

    void CrewGetUniform();

    CPlane& operator[](int index) noexcept(false);
    const CPlane& operator[](int index) const noexcept(false);

    void SaveToFile(const char* filename) const noexcept(false);

    CFlightCompany(const char* filename, int) noexcept(false);

    const int GetCrewCount() const;
};
