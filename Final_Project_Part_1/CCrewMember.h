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
    int memberID;
    static int nextID;

    void init (string name, int airTimeMinutes = 0, CAddress address = CAddress(0, "", ""));


public:
    static const int START_ID = 1000;
    CCrewMember() = delete;

    CCrewMember(string name, int airTimeMinutes = 0, CAddress address = CAddress(0, "", ""));

    CCrewMember(const CCrewMember& other);

    ~CCrewMember();

    bool UpdateMinutes(int minutes);

    string getName() const;
    CAddress getAddress() const;
    int getAirTimeMinutes() const;
    int getMemberID() const;

    void setName(string name);
    void setAddress(CAddress address);

    void Print() const;

    CCrewMember& operator=(const CCrewMember& other);

    bool operator+=(int minutes);

    bool operator==(const CCrewMember& other) const;

    friend ostream& operator<<(ostream& out, const CCrewMember& member);
};
