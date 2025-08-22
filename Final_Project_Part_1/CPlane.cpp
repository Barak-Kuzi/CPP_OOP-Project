#include <iostream>
#include "CPlane.h"

CPlane::CPlane(int serialNumber, int seatsNumber, string modelName) : serialNumber(0), seatsNumber(0), modelName("")
{
    init(serialNumber, seatsNumber, modelName);
}

CPlane::CPlane(const CPlane& other) : serialNumber(0), seatsNumber(0), modelName("")
{
    init(other.serialNumber, other.seatsNumber, other.modelName);
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

bool CPlane::IsEqual(const CPlane& other) const
{
    return this->serialNumber == other.serialNumber;
}

void CPlane::Print() const
{
    cout << "Plane "
        << serialNumber
        << " degem "
        << modelName
        << " seats "
        << seatsNumber << endl;
}

void CPlane::init(int serialNumber, int seatsNumber, string modelName)
{
    if (serialNumber > 0)
    {
        this->serialNumber = serialNumber;
    }

    if (seatsNumber > 0)
    {
        this->seatsNumber = seatsNumber;
    }

    if (!modelName.empty())
    {
        this->modelName = modelName;
    }
}
