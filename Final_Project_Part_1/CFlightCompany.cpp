#include "CFlightCompany.h"
#include <iostream>
using namespace std;

CFlightCompany::CFlightCompany(string companyName)
{
    this->companyName = companyName;
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
{
    companyName = other.companyName;
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
    this->companyName = name;
}

void CFlightCompany::Print() const
{
    cout << "Flight Company: " << companyName << endl;
}