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


    CCrewMember* getCrewMemberById(int id);
    CFlight* getFlightByNumber(int flightNumber);
    void initFlightCompanyArrays();

public:
    CFlightCompany() = delete;
    CFlightCompany(string companyName);

    CFlightCompany(const CFlightCompany& other) = delete;
    CFlightCompany& operator=(const CFlightCompany& other) = delete;

    ~CFlightCompany();

    string getCompanyName() const;

    void SetName(string name);

    void Print(ostream& out) const;

    bool AddCrewMember(const CCrewMember& crew);

    bool AddPlane(const CPlane& plane);

    bool AddFlight(const CFlight& flight);

    bool AddCrewToFlight(int flightNum, int crewMemberId);

    CPlane* GetPlane(int index);

    friend ostream& operator<<(ostream& out, const CFlightCompany& company);
};
