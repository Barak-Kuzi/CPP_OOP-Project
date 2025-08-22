#include <iostream>
#include "CFlightCompany.h"

using namespace std;

CFlightCompany::CFlightCompany(string companyName) : companyName("")
{
    SetName(companyName);
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
{
    SetName(other.companyName);
}

CFlightCompany::~CFlightCompany()
{
}

string CFlightCompany::getCompanyName() const
{
    return companyName;
}

void CFlightCompany::SetName(string name)
{
    if (!name.empty())
    {
        this->companyName = name;
    }
}

void CFlightCompany::Print() const
{
    cout << "Flight Company: " << companyName << endl;
}