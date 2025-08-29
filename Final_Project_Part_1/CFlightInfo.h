#pragma once

#include <string>
using namespace std;

class CFlightInfo
{
private:
    int flightNumber;
    string destination;
    int flightTimeMinutes;
    int flightDistanceKm;

    void init(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm);

public:
    CFlightInfo() = delete;

    CFlightInfo(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm);

    CFlightInfo(const CFlightInfo& other);

    ~CFlightInfo();

    int GetFNum() const;
    string getDestination() const;
    int getFlightTimeMinutes() const;
    int getFlightDistanceKm() const;

    void setFlightNumber(int flightNumber);
    void SetDest(string destination);
    void setFlightTimeMinutes(int flightTimeMinutes);
    void setFlightDistanceKm(int flightDistanceKm);

    bool isEqual(const CFlightInfo& other) const;
    void Print() const;

    CFlightInfo& operator=(const CFlightInfo& other);

    bool operator==(const CFlightInfo& other) const;

    bool operator!=(const CFlightInfo& other) const;

    friend ostream& operator<<(ostream& out, const CFlightInfo& info);

    operator int() const;
};
