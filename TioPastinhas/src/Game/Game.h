#include <vector>
#include <list>

#include "../Player/Player.h"
#include "../Screen/MainScreen.h"
#include "../Question/Question.h"
#include "../Card/Card.h"

class Game
{
	private:
		std::vector<Player> players;
		std::vector<Card> cards;
		std::vector<Question> questions;
		int currentRound;
		int numberRounds;

		void round(MainScreen& screen);
		void endGame();
	public:
		Game(const std::list< std::pair<std::pair<const char*, const char*>, const char*> >& infoPlayers, int numRounds);

		void startGame();
};
