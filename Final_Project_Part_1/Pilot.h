#pragma once
#include <iostream>
using namespace std;

#include "CCrewMember.h"

class CPilot : public CCrewMember
{
private:
    bool isCaptain;

protected:
    int addMinutesByRole(int baseMinutes) const override;

public:
    CPilot(const string& name = "",
        bool captain = false,
        CAddress *address = nullptr,
        int minutes = 0
        );

    bool IsCaptain() const;
    void SetCaptain(bool captainStatus);

    bool Equals(const CCrewMember& other) const override;

    void OnUniform(ostream& out) const override;
    void OnGift(ostream& out) const override;
    void OnSimulator(ostream& out) const;

    void Print(ostream& out) const override;
    CCrewMember* Clone() const override;
};
