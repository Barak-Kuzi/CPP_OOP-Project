#include <iostream>
#include "CFlightInfo.h"
#include "FlightCompException.h"

using namespace std;

CFlightInfo::CFlightInfo(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm)
    : destination(""), flightNumber(0), flightTimeMinutes(0), flightDistanceKm(0)
{
    init(destination, flightNumber, flightTimeMinutes, flightDistanceKm);
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
    : destination(""), flightNumber(0), flightTimeMinutes(0), flightDistanceKm(0)
{
    *this = other;
}

CFlightInfo::~CFlightInfo()
{
}

int CFlightInfo::GetFNum() const
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

void CFlightInfo::setFlightNumber(int num)
{
    if (num <= 0)
    {
        throw CCompStringException("Flight number must be positive");
    }
   this->flightNumber = num;
}

void CFlightInfo::SetDest(string destination)
{
    if (destination.empty())
    {
        throw CCompStringException("Destination must not be empty");
    }
        
    this->destination = destination;
}

void CFlightInfo::setFlightTimeMinutes(int minutes)
{
    if (minutes <= 0)
    {
        throw CCompStringException("Flight minutes must be positive");
    }
    this->flightTimeMinutes = minutes;
}

void CFlightInfo::setFlightDistanceKm(int km)
{
    if (km <= 0)
    {
        throw CCompStringException("Distance must be positive");
    }
    this->flightDistanceKm = km;
}

void CFlightInfo::init(string destination, int flightNumber, int flightTimeMinutes, int flightDistanceKm)
{
    SetDest(destination);
    setFlightNumber(flightNumber);
    setFlightTimeMinutes(flightTimeMinutes);
    setFlightDistanceKm(flightDistanceKm);
}

CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other)
{
    if (this != &other)
    {
        init(other.destination, other.flightNumber, other.flightTimeMinutes, other.flightDistanceKm);
    }
    return *this;
}

bool CFlightInfo::operator==(const CFlightInfo& other) const
{
    return (flightNumber == other.flightNumber &&
        flightDistanceKm == other.flightDistanceKm &&
        destination == other.destination &&
        flightTimeMinutes == other.flightTimeMinutes);
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
    return !(*this == other);
}

ostream& operator<<(ostream& out, const CFlightInfo& flightInfo)
{
    out << "Flight Info dest: "
        << flightInfo.destination
        << " Number "
        << flightInfo.flightNumber
        << " minutes "
        << flightInfo.flightTimeMinutes
        << " KM "
        << flightInfo.flightDistanceKm << endl;
    return out;
}

CFlightInfo::operator int() const
{
    return flightTimeMinutes;
}
