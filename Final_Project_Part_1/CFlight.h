#pragma once

#include <iostream>
#include "CFlightInfo.h"
#include "CPlane.h"
#include "CCrewMember.h"

using namespace std;

const int MAX_CREW = 10;

class CFlight
{
private:
    CFlightInfo flightInfo;
    CPlane* plane;
    CCrewMember* crewMembers[MAX_CREW];
    int crewCount;

    void initCrewMembersArr();

public:
    CFlight() = delete;

    CFlight(const CFlightInfo& info);

    CFlight(const CFlightInfo& info, CPlane* plane);

    CFlight(const CFlight& other);

    ~CFlight();

    CFlight& operator=(const CFlight& other);

    const CFlightInfo getFlightInfo() const;
    void SetPlane(CPlane* newPlane);

    const CPlane getPlane() const;
    const CCrewMember* getCrewMember() const;
    const int getCrewMembersCount() const;

    friend CFlight& operator+(CFlight& f, const CCrewMember& crew);

    friend ostream& operator<<(ostream& out, const CFlight& flight);

    bool operator==(const CFlight& other) const;
};
