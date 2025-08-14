#pragma once

#include <string>
#include "CAddress.h"
using namespace std;

class CCrewMember
{
private:
    string name;
    int airTimeMinutes;
    CAddress address;

public:
    CCrewMember(string name, CAddress address, int airTimeMinutes = 0);

    CCrewMember(const CCrewMember& other);

    ~CCrewMember();

    bool UpdateMinutes(int minutes);

    string getName() const;
    CAddress getAddress() const;
    int getAirTimeMinutes() const;

    void setName(string name);
    void setAddress(CAddress address);

    bool IsEqual(const CCrewMember& other) const;

    void Print() const;
};
