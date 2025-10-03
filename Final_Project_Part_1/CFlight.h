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

    CFlight(const CFlightInfo& info, CPlane* plane = nullptr);

    CFlight(const CFlight& other);

    ~CFlight();

    CFlight& operator=(const CFlight& other);

    const CFlightInfo& GetFlightInfo() const;
    void SetPlane(CPlane* newPlane);

    const CPlane getPlane() const;
    const CCrewMember* getCrewMember() const;
    const int getCrewMembersCount() const;

    friend CFlight& operator+(CFlight& f, const CCrewMember& crew);
    friend CFlight& operator+(CFlight& f, const CCrewMember* pCrew);

    friend ostream& operator<<(ostream& out, const CFlight& flight);

    bool operator==(const CFlight& other) const;

    bool TakeOff() noexcept(false);
    
    CPlane* GetPlanePtr();
    const CPlane* GetPlanePtr() const;

    const CCrewMember* GetCrewMemberAt(int index) const noexcept(false);
};
