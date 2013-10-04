#include <string>
#include <vector>

class Question
{
	private:
		std::string text;
		std::vector<std::string> options;
		int correct;
		int type;
	public:
		Question(std::string text, const std::vector<std::string>& options);
		
		char* getText();
		char* getOptions(int option);
		int getCorrectOption();
		int getType(); 
};
