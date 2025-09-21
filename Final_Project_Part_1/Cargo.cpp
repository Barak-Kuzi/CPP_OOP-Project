#include "Cargo.h"

CCargo::CCargo(int seats, const string& model, float maxKgVal, float maxVolM3)
    : CPlane(seats, model),
    maxKg(maxKgVal),
    maxVol(maxVolM3),
    currKg(0.0f),
    currVol(0.0f)
{
}

bool CCargo::Load(float kg, float volM3)
{
    if (volM3 < 0.0f || kg < 0.0f)
    {
        return false;
    }

    if (currVol + volM3 > maxVol)
    {
        return false;
    }

    if (currKg + kg > maxKg)
    {
        return false;
    }

    currVol += volM3;
    currKg += kg;
    return true;
}

void CCargo::PrintTakeoffLog(int minutes, ostream& out) const
{
    out << "Need to add " << minutes << " to my log book" << endl;
}

void CCargo::OnTakeoff(int minutes) const
{
    cout << "Need to add " << minutes << " minutes to my log book" << endl;
}

float CCargo::GetMaxKg() const
{
    return maxKg;
}

float CCargo::GetMaxVol() const
{
    return maxVol;
}

float CCargo::GetCurrKg() const
{
    return currKg;
}

float CCargo::GetCurrVol() const
{
    return currVol;
}

void CCargo::Print(ostream& out) const
{
    out << "Cargo M_vol " << GetMaxVol();
    out << " M_Kg " << GetMaxKg();
    out << " C_vol " << GetCurrVol();
    out << " C_Kg " << GetCurrKg() << endl;
}

CPlane* CCargo::Clone() const
{
    return new CCargo(*this);
}
