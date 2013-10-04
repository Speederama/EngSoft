#include <cstdio>

#include "Game.h"

using namespace std;

Game::Game(list< pair<pair<const char*, const char*>, const char*> > infoPlayers, int numRounds)
{
	for (list< pair<pair<const char*, const char*>, const char*> >::iterator it = infoPlayers.begin(); it != infoPlayers.end(); ++it)
	{
		Player player(it->first.first, it->first.second, it->second);
		players.push_back(player);
	}

	numberRounds = numRounds;
	currentRound = 1;
}

void Game::startGame()
{
	MainScreen screen;
	while (currentRound <= numberRounds)
	{
		round(screen);
		currentRound++;
	}

	endGame();
}

void Game::round(MainScreen screen)
{
	list< pair<const char*, int> > info;
	for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
		info.push_back(pair<const char*, int>(it->getName(), it->getPoints()));

	for (int i = 0; i < players.size(); ++i)
	{
		Player current = players[i];
		list< pair<const char*, int> > companyInfo;
		for (list<Company>::iterator it = current.getCompanies().begin(); it != current.getCompanies().end(); ++it)
			companyInfo.push_back(pair<const char*, int>(it->getName(), it->getLevel()));

		list< pair<const char*, int> > copy = info;
		int count = 0;
		for (list< pair<const char*, int> >::iterator it = copy.begin(); it != copy.end(); ++it)
		{
			if (count == i)
				copy.erase(it);
			count++;
		}

		//TODO: Deal with outcome here...
		int outcome = 0;
		while (outcome < 1 || outcome > 10 )
		{
			screen.drawScreen(current.getFileAvatar(), currentRound, numberRounds, current.getName(), current.getMethodology(), 
				current.getPoints(), current.getResources(), companyInfo, copy);
			outcome = screen.waitForEvent();

			//Outcome 1-4: General Question
			if (outcome >= 1 && outcome <= 4)
			{
				int correct = 1;
				if (outcome == correct)
					players[i].addResources(100000);
				else
					players[i].removeResources(100000);
			}
			//Outcome 5-8: Specific question
			else if (outcome >=5 && outcome <= 8)
			{
				int correct = 5;
				if (outcome == correct)
					players[i].addResources(200000);
				else
					players[i].removeResources(200000);
			}
			//Outcome 9: Lucky card
			else if (outcome == 9)
			{
				players[i].addResources(500000);
			}
			//Outcome 10: Bad luck card
			else if (outcome == 10)
			{
				players[i].removeResources(500000);
			}
			//Outcome 11: Company purchase
			else if (outcome == 11)
			{
				int num = players[i].getNumEmpresas();
				char name[1024];
				sprintf(name, "Empresa %d", num + 1);
				players[i].buyCompany(name);
			}
			//Outcome 12+: Certifications
			else if (outcome >= 12)
			{
				int index = outcome - 11;
				for (list<Company>::iterator it = players[i].getCompanies().begin(); it != players[i].getCompanies().end(); ++it)
				{
					--index;
					if (index == 0)
						players[i].certifyCompany(it->getName());
				}
			}
		}
	}
}

void Game::endGame()
{
	//TODO
}
