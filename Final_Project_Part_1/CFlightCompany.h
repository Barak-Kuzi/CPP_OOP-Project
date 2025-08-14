#pragma once

#include <string>
using namespace std;

class CFlightCompany
{
private:
    string companyName;

public:
    CFlightCompany(string companyName);

    CFlightCompany(const CFlightCompany& other);

    ~CFlightCompany();

    string getCompanyName() const;

    void SetName(string name);

    void Print() const;
};
