#include <vector>
#include <list>

#include "Player.h"
#include "MainScreen.h"
#include "Question.h"
#include "Card.h"

class Game
{
	private:
		std::vector<Player> players;
		int currentRound;
		int numberRounds;

		void round(MainScreen& screen);
		void endGame();
	public:
		Game(const std::list< std::pair<std::pair<const char*, const char*>, const char*> >& infoPlayers, int numRounds);

		void startGame();
};
