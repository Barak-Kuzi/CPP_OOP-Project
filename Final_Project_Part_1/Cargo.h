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

    void init(int seats, const string& model, float maxKg, float maxVol, float currKg, float currVol);
    bool IsPositive(float val);
    void setMaxValues(int maxKG, int maxVolume) noexcept(false);

public:
    CCargo() = delete;
    CCargo(int seats = 0, 
        const string& model = "CargoModel",
        float maxKg = 0.0f,
        float maxVol = 0.0f);

    CCargo(const CCargo& other);
    CCargo& operator=(const CCargo& other);
    ~CCargo();

    bool Load(float kg, float volM3);

    void OnTakeoff(int minutes) const override;

    void SetMaxKg(float v) noexcept(false);
    void SetMaxVol(float v) noexcept(false);
    void SetCurrKg(float v) noexcept(false);
    void SetCurrVol(float v) noexcept(false);
    void SetCurrentLoad(int currKg, int maxKg, int currVol, int maxVol) noexcept(false);

    float GetMaxKg() const;
    float GetMaxVol() const;
    float GetCurrKg() const;
    float GetCurrVol() const;

    void Print(ostream& out) const override;

    CPlane* Clone() const override;
};
