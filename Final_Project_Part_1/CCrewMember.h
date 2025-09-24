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

protected:
    virtual int addMinutesByRole(int baseMinutes) const;
    void init(string name, int airTimeMinutes = 0, CAddress address = CAddress(0, "", "Tel Aviv"));

public:
    CCrewMember() = delete;

    CCrewMember(string name, int airTimeMinutes = 0, CAddress address = CAddress(0, "", "Tel Aviv"));

    CCrewMember(const CCrewMember& other);

    virtual ~CCrewMember();

    bool UpdateMinutes(int minutes);

    const string& getName() const;
    const CAddress& getAddress() const;
    int getAirTimeMinutes() const;

    void setName(string name);
    void setAddress(CAddress address);

    CCrewMember& operator=(const CCrewMember& other);

    bool operator+=(int minutes);

    bool operator==(const CCrewMember& other) const;
    bool operator!=(const CCrewMember& other) const;

    friend ostream& operator<<(ostream& out, const CCrewMember& member);

    virtual void Print(ostream& out) const = 0;

    virtual void OnUniform(ostream& out) const = 0;

    virtual void OnGift(ostream& out) const;

    virtual bool Equals(const CCrewMember& other) const;

    virtual CCrewMember* Clone() const = 0;
};
