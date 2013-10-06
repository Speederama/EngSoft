#include <cstring>
#include <cstdlib>

#include "Company.h"

Company::Company(const char* name)
{
	nameCompany = name;
	levelCMMI = 1;
}

void Company::upLevel()
{
	if (levelCMMI < 5)
		levelCMMI += 1;
}

void Company::downLevel()
{
	if (levelCMMI > 1)
		levelCMMI -= 1;
}

int Company::getCertificationCost() const
{
	//TODO

	return 100000 * levelCMMI;
}
