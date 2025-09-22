#pragma once
#include <iostream>
using namespace std;

#include "CPlane.h"

class CCargo : public CPlane
{
private:
    float maxKg;   
    float maxVol;
    float currKg; 
    float currVol; 

public:
    CCargo() = delete;
    CCargo(int seats = 0, 
        const string& model = "CargoModel",
        float maxKgVal = 0.0f,
        float maxVolM3 = 0.0f);

    CCargo(const CCargo& other);
    CCargo& operator=(const CCargo& other);
    ~CCargo();

    bool Load(float kg, float volM3);

    void PrintTakeoffLog(int minutes, ostream& out) const;
    void OnTakeoff(int minutes) const override;

    float GetMaxKg() const;
    float GetMaxVol() const;
    float GetCurrKg() const;
    float GetCurrVol() const;

    void ResetCargo() { currKg = 0.0f; currVol = 0.0f; }
    friend ostream& operator<<(ostream& out, const CCargo& c);
    void Print(ostream& out) const override;

    CPlane* Clone() const override;
};
