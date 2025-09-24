#pragma once

#include <string>
using namespace std;

class CPlane
{
private:
    int serialNumber;
    string modelName;
    int seatsNumber;
    static int nextSerial;

protected:
    void init(int seatsNumber, string modelName);

public:
    static const int START_ID = 100;
    CPlane() = delete;

    CPlane(int seatsNumber, string modelName);

    CPlane(const CPlane& other);

    virtual ~CPlane();

    int getSerialNumber() const;
    string getModelName() const;
    int getSeatsNumber() const;

    CPlane& operator=(const CPlane& other);

    bool operator==(const CPlane& other) const;

    friend ostream& operator<<(ostream& out, const CPlane& plane);

    CPlane& operator++();

    CPlane operator++(int);
    virtual void Print(ostream& out) const;
    virtual CPlane* Clone() const;
    virtual void OnTakeoff(int minutes) const;
};
