#include "Cargo.h"
#include "FlightCompException.h"

void CCargo::init(int seats, const string& model, float maxKg, float maxVol, float currKg, float currVol)
{
    CPlane::init(seats, model);
    SetMaxKg(static_cast<float>(maxKg));
    SetMaxVol(static_cast<float>(maxVol));
    SetCurrKg(static_cast<float>(currKg));
    SetCurrVol(static_cast<float>(currVol));
}

bool CCargo::IsPositive(float val)
{
    return val >= 0.0f;
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
    //if (!IsPositive(v) || (maxKg > 0.0f && v > maxKg))
    //{
    //    return;
    //}
    if (!IsPositive(v))
        throw CCompStringException("Current KG must be positive");
    if (maxKg > 0.0f && v > maxKg)
        throw CCompStringException("Current KG exceeds max KG");
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


void CCargo::setMaxValues(int maxKG, int maxVolume) noexcept(false)
{
    if (maxKG <= 0 || maxVolume <= 0)
    {
        throw CCompStringException("Cargo max KG/Volume must be positive");
    }
    this->maxKg = static_cast<float>(maxKG);
    this->maxVol = static_cast<float>(maxVolume);
}

void CCargo::SetCurrentLoad(int currKg, int maxKg, int currVol, int maxVol) noexcept(false)
{
    setMaxValues(maxKg, maxVol);
    if (currKg < 0 || currVol < 0)
    {
        throw CCompStringException("Negative cargo load");
    }
    this->currKg = static_cast<float>(currKg);
    this->currVol = static_cast<float>(currVol);
    if (this->currKg > this->maxKg || this->currVol > this->maxVol)
    {
        throw CCompStringException("Current cargo exceeds max capacity");
    }
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
