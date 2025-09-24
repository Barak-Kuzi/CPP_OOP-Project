#include "Cargo.h"

void CCargo::init(int seats, const string& model, float maxKg, float maxVol, float currKg, float currVol)
{
    CPlane::init(seats, model);
    SetMaxKg(maxKg);
    SetMaxVol(maxVol);
    SetCurrKg(currKg);
    SetCurrVol(currVol);
}

bool CCargo::IsPositive(float val)
{
    return val > 0.0f;
}

CCargo::CCargo(int seats, const string& model, float maxKg, float maxVol)
    : CPlane(seats, model),
    maxKg(maxKg),
    maxVol(maxVol),
    currKg(0.0f),
    currVol(0.0f)
{
    init(seats, model, maxKg, maxVol, 0.0f, 0.0f);
}

CCargo::CCargo(const CCargo& other)
    : CPlane(other),
    maxKg(other.GetMaxKg()),
    maxVol(other.GetMaxVol()),
    currKg(other.GetCurrKg()),
    currVol(other.GetCurrVol())
{
}

CCargo& CCargo::operator=(const CCargo& other)
{
    if (this != &other) {
        CPlane::operator=(other);
        maxKg = other.GetMaxKg();
        maxVol = other.GetMaxVol();
        currKg = other.GetCurrKg();
        currVol = other.GetCurrVol();
    }
    return *this;
}

CCargo::~CCargo()
{
}


void CCargo::SetMaxKg(float v)
{
    if (!IsPositive(v) || currKg > v)
    {
        return;
    }
    maxKg = v;
}

void CCargo::SetMaxVol(float v)
{
    if (!IsPositive(v) || currVol > v)
    {
        return;
    }
    maxVol = v;
}

void CCargo::SetCurrKg(float v)
{
    if (!IsPositive(v) || (maxKg > 0.0f && v > maxKg))
    {
        return;
    }
    currKg = v;
}

void CCargo::SetCurrVol(float v)
{
    if (!IsPositive(v) || (maxVol > 0.0f && v > maxVol))
    {
        return;
    }
    currVol = v;
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
