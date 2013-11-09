#include <cstdlib>
#include <cstring>

#include "Player.h"

using namespace std;

Player::Player(const char* namePlayer, const char* methodologyPlayer, const char* fileAvatar)
{
	Player::namePlayer = namePlayer;
	Player::methodologyPlayer = methodologyPlayer;
	Player::fileAvatar = fileAvatar;

	pointsPlayer = 0;
	resourcesPlayer = INITIAL_RESOURCES;
}

void Player::addResources(int resources)
{
	if (resources > 0)
		resourcesPlayer += resources;
}

int Player::removeResources(int resources, bool force)
{
	if (resources > 0 && resources <= resourcesPlayer)
	{
		resourcesPlayer -= resources;
		return 1;
	}
	else if (force)
	{
		resourcesPlayer = 0;
		return 1;
	}
	return 0;
}

int Player::buyCompany(const char* nameCompany)
{
	for (list<Company>::iterator it = listCompanies.begin(); it != listCompanies.end(); ++it)
	{
		if (strcmp(it->getName(), nameCompany) == 0)
			return -1;
	}
	if (removeResources(COMPANY_PRICE, false) == 1)
	{
		Company company(nameCompany);
		listCompanies.push_back(company);
		updatePoints();
		return 1;
	}
	else
		return 0;
}

int Player::certifyCompany(const char* nameCompany)
{
	for (list<Company>::iterator it = listCompanies.begin(); it != listCompanies.end(); ++it)
	{
		if (strcmp(it->getName(), nameCompany) == 0)
		{
			if (removeResources(it->getCertificationCost(), false) == 1)
			{
				it->upLevel();
				updatePoints();
				return 1;
			}
			else
				return 0;
		}
	}

	return -1;
}

void Player::updatePoints()
{
	int sumLevel = 0;
	for (list<Company>::iterator it = listCompanies.begin(); it != listCompanies.end(); ++it)
		sumLevel += it->getLevel() - 1;
	pointsPlayer = 100 * getNumEmpresas() + 50 * sumLevel;
}
