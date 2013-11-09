# include <string>
# include <vector>
# include <fstream>
# include <iostream>
# include <sstream>


class Question {

public:

	const int id;
	const int type;
	const int correct;
	const std::string text;
	const std::vector<std::string> option;

	// Constructor
	Question(const int& type, const int& corret, const int id,
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
		const int id, const std::string& text,
		const std::vector<std::string>& option) :
type(type), correct(correct), text(text), option(option), id(id) {
}

// Destructor
inline Question::~Question(void) {
}

// Loads the set of cards
inline void Question::loader(const std::string& path,
		std::vector<Question *>& question) {

	std::string text;
	int id, type, correct;

	FILE* fp = fopen(path.data(), "r");
	if (fp != NULL) {
		// Ignoring first two lines...
		char aux[1000];
		if (fgets(aux, 1000, fp) == NULL) return;
		if (fgets(aux, 1000, fp) == NULL) return;

		while (fgets(aux, 1000, fp) != NULL) {
			std::vector<std::string> options;
			char* p = strtok(aux, "|\n");
			id = atoi(p);
			p = strtok(NULL, "|\n");
			type = atoi(p);
			p = strtok(NULL, "|\n");
			text = p;
			p = strtok(NULL, "|\n");
			options.push_back(std::string(p));	
			p = strtok(NULL, "|\n");
			options.push_back(std::string(p));	
			p = strtok(NULL, "|\n");
			options.push_back(std::string(p));	
			p = strtok(NULL, "|\n");
			options.push_back(std::string(p));	
			p = strtok(NULL, "|\n");
			switch(p[0]) {
			case 'A':
				correct = 1;
				break;
			case 'B':
				correct = 2;
				break;
			case 'C':
				correct = 3;
				break;
			case 'D':
				correct = 4;
				break;
			}

			Question* q = new Question(type, correct, id, 
				text, options);
			question.push_back(q);
		}

		fclose(fp);
	}
}
