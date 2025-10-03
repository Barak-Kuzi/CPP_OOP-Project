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

    void setFlightNumber(int flightNumber) noexcept(false);
    void SetDest(string destination) noexcept(false);
    void setFlightTimeMinutes(int flightTimeMinutes) noexcept(false);
    void setFlightDistanceKm(int flightDistanceKm) noexcept(false);

    CFlightInfo& operator=(const CFlightInfo& other);

    bool operator==(const CFlightInfo& other) const;

    bool operator!=(const CFlightInfo& other) const;

    friend ostream& operator<<(ostream& out, const CFlightInfo& info);

    operator int() const;
};
