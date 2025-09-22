#pragma once
#include <iostream>
using namespace std;

#include "CCrewMember.h"

class CHost : public CCrewMember
{
public:
    enum HostType { eRegular = 0, eSuper = 1, eCalcelan = 2 };

private:
    HostType type;

public:
    CHost() = delete;
    CHost(const string& name = "",
        HostType t = eRegular,
        CAddress* addr = new CAddress(0, "", "Tel Aviv"),
        int minutes = 0
    );

    CHost(const CHost& other);
    CHost& operator=(const CHost& other);
    ~CHost();

    HostType GetType() const;
    void SetType(HostType t);

    bool Equals(const CCrewMember& other) const override;

    void OnUniform(ostream& out) const override;
    void OnGift(ostream& out) const override;
    void Print(ostream& out) const override;
    CCrewMember* Clone() const override;
};
