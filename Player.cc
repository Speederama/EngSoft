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

void Player::removeResources(int resources)
{
	if (resources > 0 && resources < resourcesPlayer)
		resourcesPlayer -= resources;
}

int Player::buyCompany(const char* nameCompany)
{
	for (list<Company>::iterator it = listCompanies.begin(); it != listCompanies.end(); ++it)
	{
		if (strcmp(it->getName(), nameCompany) == 0)
			return -1;
	}
	if (resourcesPlayer >= COMPANY_PRICE)
	{
		resourcesPlayer -= COMPANY_PRICE;
		Company company(nameCompany);
		listCompanies.push_back(company);
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
			if (it->getCertificationCost() <= resourcesPlayer)
			{
				resourcesPlayer -= it->getCertificationCost();
				it->upLevel();
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
  //TODO
}
