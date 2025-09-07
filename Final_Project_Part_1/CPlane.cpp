#include <iostream>
#include "CPlane.h"

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
    if (seatsNumber > 0)
    {
        this->seatsNumber = seatsNumber;
    }

    if (!modelName.empty())
    {
        this->modelName = modelName;
    }
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
    return out;
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
