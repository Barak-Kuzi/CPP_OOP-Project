#pragma once

#include <string>
using namespace std;

class CPlane
{
private:
    int serialNumber;
    string modelName;
    int seatsNumber;

    void init(int serialNumber, int seatsNumber, string modelName);

public:
    CPlane(int serialNumber, int seatsNumber, string modelName);

    CPlane(const CPlane& other);

    ~CPlane();

    int getSerialNumber() const;
    string getModelName() const;
    int getSeatsNumber() const;

    bool IsEqual(const CPlane& other) const;

    void Print() const;
};
