#include <iostream>
#include "CPlane.h"
#include "Cargo.h"
#include "FlightCompException.h"

int CPlane::nextSerial = CPlane::START_ID;

CPlane::CPlane(int seatsNumber, string modelName) : serialNumber(nextSerial++), seatsNumber(0), modelName("")
{
    init(seatsNumber, modelName);
}

CPlane::CPlane(const CPlane& other) : serialNumber(other.serialNumber), seatsNumber(0), modelName("")
{
    *this = other;
}

CPlane::~CPlane()
{
}

int CPlane::getSerialNumber() const
{
    return serialNumber;
}

string CPlane::getModelName() const
{
    return modelName;
}

int CPlane::getSeatsNumber() const
{
    return seatsNumber;
}

void CPlane::init(int seatsNumber, string modelName)
{
    if (seatsNumber <= 0)
    {
        throw CCompStringException("Seats must be positive");
    }
    if (modelName.empty())
    {
        throw CCompStringException("Model must not be empty");
    }
    this->seatsNumber = seatsNumber;
    this->modelName = modelName;
}

CPlane& CPlane::operator=(const CPlane& other)
{
    if (this != &other)
    {
        init(other.seatsNumber, other.modelName);
    }
    return *this;
}

bool CPlane::operator==(const CPlane& other) const
{
    return this->serialNumber == other.serialNumber;
}

ostream& operator<<(ostream& out, const CPlane& plane)
{
    out << "Plane " << plane.serialNumber
        << " degem " << plane.modelName
        << " seats " << plane.seatsNumber << endl;

    if (typeid(plane) == typeid(CCargo))
    {
        plane.Print(out);
    }

    return out;
}

void CPlane::Print(ostream& out) const
{
   
}

CPlane& CPlane::operator++()
{
    seatsNumber++;
    return *this;
}

CPlane CPlane::operator++(int)
{
    CPlane temp = *this;
    seatsNumber++;
    return temp;
}

CPlane* CPlane::Clone() const
{
    return new CPlane(*this);
}

void CPlane::OnTakeoff(int minutes) const
{
}

int CPlane::GetNextSerial()
{
    return nextSerial;
}

void CPlane::SetNextSerial(int next)
{
    if (next > 0)
    {
        nextSerial = next;
    }
}

void CPlane::SetSerialNumber_ForLoad(int id)
{
    if (id > 0)
    {
        serialNumber = id;
        if (id >= nextSerial)
        {
            nextSerial = id + 1;
        }
    }
}
