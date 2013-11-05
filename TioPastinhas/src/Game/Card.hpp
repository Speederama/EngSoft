# include <string>
# include <fstream>
# include <iostream>
# include "../Allegro/Allegro.hpp"


class Card {

public:

	const int id;
	const int effect;
	const int magnitude;
	Allegro::Image *image;

	// Constructor
	Card(const ALLEGRO_EVENT& event, const int&id, const int& effect,
			const int& magnitude, const std::string& path);

	// Destructor
	~Card(void);

	// Loads the set of cards
	static void loader(const ALLEGRO_EVENT& event,
			const std::string& path, std::vector<Card *>& card);

private:

	const std::string _path;

};


// Constructor
inline Card::Card(const ALLEGRO_EVENT& event, const int&id,
		const int& effect, const int& magnitude,
		const std::string& path) :
id(id), effect(effect), magnitude(magnitude), _path(path) {

	image = new Allegro::Image(event, path);
	if (image == NULL) config::error::load(path);

}

// Destructor
inline Card::~Card(void) {
	delete image;
}

// Loads the set of cards
inline void Card::loader(const ALLEGRO_EVENT& event,
		const std::string& path, std::vector<Card *>& card) {

	/*
	std::string img_path;
	int id, effect, magnitude;

	std::string line;
	std::stringstream ss;
	std::ifstream infile(path);

	while (std::getline(infile, line) and (ss << line)) {

		ss >> id >> effect >> magnitude >> img_path;
		card.push_back(new Card(event, id, effect,
					magnitude, img_path));

	}

	infile.close();
	*/

}
