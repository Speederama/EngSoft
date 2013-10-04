#include <cstring>
#include <cstdlib>

#include "Company.h"

Company::Company(const char* name)
{
	nameCompany = (char*) malloc(sizeof(char) * (strlen(name) + 1 ));
	strcpy(nameCompany, name);
	levelCMMI = 1;
}

Company::~Company()
{
	if (nameCompany != NULL)
		free(nameCompany);
}

char* Company::getName()
{
	return nameCompany;
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

int Company::getLevel()
{
	return levelCMMI;
}

int Company::getCertificationCost()
{
	//TODO

	return 100000;
}
