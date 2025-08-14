#include "CPlane.h"

CPlane::CPlane(int serialNumber, int seatsNumber, string modelName)
{
    init(serialNumber, seatsNumber, modelName);
}

CPlane::CPlane(const CPlane& other)
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
    this->serialNumber = (serialNumber > 0) ? serialNumber : 0;
    this->seatsNumber = (seatsNumber > 0) ? seatsNumber : 0;
    this->modelName = modelName;
}
