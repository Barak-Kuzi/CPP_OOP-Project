#pragma once


enum PlaneType
{
	eRegular,
	eCargo,
	nofPlaneType
};

enum CrewType
{
	eHost,
	ePilot,
	nofCrewType
};
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;


const string PlaneType_TITLE[nofPlaneType] = { "Regular","Cargo" };
const string CrewType_TITLE[nofCrewType] = { "Host","Pilot" };


class CPlane;
class CCrewMember;
class CFlightCompany;
class CAddress;

class CPlaneCrewFactory
{
public:

	static PlaneType GetPlaneType(const CPlane* pPlane);
	static CrewType GetCrewType(const CCrewMember* pCrew);
	static void GetCompanyDataFromUser(CFlightCompany& comp);
	static CPlane* GetPlaneFromUser() noexcept(false);
	static CCrewMember* GetCrewFromUser() noexcept(false);

	static CCrewMember* GetCrewMemberFromFile(ifstream& inFile) noexcept(false);
	static CPlane* GetPlaneFromFile(ifstream& inFile) noexcept(false);


private:
	CPlaneCrewFactory(void) { ; }
	static int askInt(const char* prompt);
	static string askStr(const char* prompt);
};
