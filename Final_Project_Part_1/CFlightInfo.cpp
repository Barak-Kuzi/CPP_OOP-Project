#include <iostream>
#include "CFlightInfo.h"

using namespace std;

CFlightInfo::CFlightInfo(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm)
    : destination(""), flightNumber(0), flightTimeMinutes(0), flightDistanceKm(0)
{
    init(destination, flightNumber, flightTimeMinutes, flightDistanceKm);
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
    : destination(""), flightNumber(0), flightTimeMinutes(0), flightDistanceKm(0)
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
    if (flightNumber > 0) 
    {
        this->flightNumber = flightNumber;
    }
}

void CFlightInfo::SetDest(string destination)
{
    if (!destination.empty()) 
    {
        this->destination = destination;
    }
}

void CFlightInfo::setFlightTimeMinutes(int flightTimeMinutes)
{
    if (flightTimeMinutes > 0)
    {
        this->flightTimeMinutes = flightTimeMinutes;
    }
}

void CFlightInfo::setFlightDistanceKm(int flightDistanceKm)
{
    if (flightDistanceKm > 0) 
    {
        this->flightDistanceKm = flightDistanceKm;
    }
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
