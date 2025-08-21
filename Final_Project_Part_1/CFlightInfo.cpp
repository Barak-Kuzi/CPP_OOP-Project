#include <iostream>
#include "CFlightInfo.h"

using namespace std;

CFlightInfo::CFlightInfo(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm)
{
    init(destination, flightNumber, flightTimeMinutes, flightDistanceKm);
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
{
    init(other.destination, other.flightNumber, other.flightTimeMinutes, other.flightDistanceKm);
}

CFlightInfo::~CFlightInfo()
{
}

int CFlightInfo::getFlightNumber() const
{
    return flightNumber;
}

string CFlightInfo::getDestination() const
{
    return destination;
}

int CFlightInfo::getFlightTimeMinutes() const
{
    return flightTimeMinutes;
}

int CFlightInfo::getFlightDistanceKm() const
{
    return flightDistanceKm;
}

void CFlightInfo::setFlightNumber(int flightNumber)
{
    this->flightNumber = (flightNumber > 0) ? flightNumber : 0;
}

void CFlightInfo::SetDest(string destination)
{
    this->destination = !destination.empty() ? destination : "";
}

void CFlightInfo::setFlightTimeMinutes(int flightTimeMinutes)
{
    this->flightTimeMinutes = (flightTimeMinutes > 0) ? flightTimeMinutes : 0;
}

void CFlightInfo::setFlightDistanceKm(int flightDistanceKm)
{
    this->flightDistanceKm = (flightDistanceKm > 0) ? flightDistanceKm : 0;
}

bool CFlightInfo::isEqual(const CFlightInfo& other) const
{
    return this->flightNumber == other.flightNumber;
}

void CFlightInfo::Print() const
{
    cout << "Flight Info dest: "
        << destination
        << " Number "
        << flightNumber
        << " minutes "
        << flightTimeMinutes
        << " KM "
        << flightDistanceKm << endl;
}

void CFlightInfo::init(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm)
{
    SetDest(destination);
    setFlightNumber(flightNumber);
    setFlightTimeMinutes(flightTimeMinutes);
    setFlightDistanceKm(flightDistanceKm);
}
