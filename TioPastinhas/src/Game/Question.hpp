# include <string>
# include <vector>
# include <fstream>
# include <iostream>


class Question {

public:

	const int type;
	const int correct;
	const std::string text;
	const std::vector<std::string> option;

	// Constructor
	Question(const int& type, const int& corret,
			const std::string& text,
			const std::vector<std::string>& option);

	// Destructor
	~Question(void);

	// Loads the set of cards
	static void loader(const std::string& path,
		std::vector<Question *>& question);

};


// Constructor
inline Question::Question(const int& type, const int& correct,
		const std::string& text,
		const std::vector<std::string>& option) :
type(type), correct(correct), text(text), option(option) {
}

// Destructor
inline Question::~Question(void) {
}

// Loads the set of cards
inline void Question::loader(const std::string& path,
		std::vector<Question *>& card) {

	/*
	std::string img_path;
	int id, effect, magnitude;

	std::string line;
	std::stringstream ss;
	std::ifstream infile(path);

	while (std::getline(infile, line) and (ss << line)) {

		ss >> id >> effect >> magnitude >> img_path;
		card.push_back(new Question(event, id, effect,
					magnitude, img_path));

	}
	*/

}
