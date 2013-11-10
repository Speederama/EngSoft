# include <string>
# include <fstream>
# include <iostream>
# include "../Allegro/Allegro.hpp"


class Card {

public:

	const int id;
	const int type;
	const int effect;
	const int magnitude;
	std::string description;

	// Constructor
	Card(const int&id, const int& type, const int& effect, 
		const int& magnitude, const std::string& description);

	// Destructor
	~Card(void);

	// Loads the set of cards
	static void loader(const std::string& path, 
		std::vector<Card *>& card);

};


// Constructor
inline Card::Card(const int& id, const int& type, 
		const int& effect, const int& magnitude,
		const std::string& description) :
id(id), type(type), effect(effect), magnitude(magnitude), 
description(description) {}

// Destructor
inline Card::~Card(void) {}

// Loads the set of cards
inline void Card::loader(const std::string& path, 
	std::vector<Card *>& card) {

	std::string description;
	int id, type, effect, magnitude;

	FILE* fp = fopen(path.data(), "r");
        if (fp != NULL) {
                // Ignoring first three lines...
                char aux[1000];
                if (fgets(aux, 1000, fp) == NULL) return;
                if (fgets(aux, 1000, fp) == NULL) return;
                if (fgets(aux, 1000, fp) == NULL) return;

                while (fgets(aux, 1000, fp) != NULL) {
			char* p = strtok(aux, "|\n");
                        id = atoi(p);
                        p = strtok(NULL, "|\n");
                        type = atoi(p);
                        p = strtok(NULL, "|\n");
                        effect = atoi(p);
                        p = strtok(NULL, "|\n");
                        magnitude = atoi(p);
                        p = strtok(NULL, "|\n");
                        description = p;

			Card* c = new Card(id, type, effect, 
				magnitude, description);
			card.push_back(c);
		}
	}
}
