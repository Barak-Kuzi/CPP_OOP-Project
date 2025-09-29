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
    CPilot() = delete;
    CPilot(const string& name = "",
        bool captain = false,
        const CAddress* address = nullptr,
        int minutes = 0
        );

    CPilot(const CPilot& other);
    CPilot& operator=(const CPilot& other);
    ~CPilot();

    bool IsCaptain() const;
    void SetCaptain(bool captainStatus);

    bool Equals(const CCrewMember& other) const override;

    void OnUniform(ostream& out) const override;
    void OnGift(ostream& out) const override;
    void OnSimulator(ostream& out) const;

    void Print(ostream& out) const override;
    CCrewMember* Clone() const override;
};
