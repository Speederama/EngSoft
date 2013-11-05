# ifndef DATA_HPP
# define DATA_HPP

# include "Card.hpp"
// # include "Player.hpp"
// # include "Company.hpp"
# include "Question.hpp"


struct Data {

public:

	int num_rounds, cur_round;

	std::vector<Card *> card;
	// std::vector<Player *> player;
	// std::vector<Company *> company;
	std::vector<Question *> question;

	// Constructor
	inline Data() :
	num_rounds(0), cur_round(0) {
	}

	// Destructor
	inline ~Data() {

		for (int i(0); i < card.size(); ++i) delete card[i];
		// for (int i(0); i < player.size(); ++i) delete player[i];
		// for (int i(0); i < company.size(); ++i) delete company[i];
		for (int i(0); i < question.size(); ++i) delete question[i];

		card.clear();
		// player.clear();
		// company.clear();
		question.clear();

	}

};

# endif
