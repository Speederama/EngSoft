#include <string>

class Card
{
	private:
		std::string image;
		int effect;
		int magnitude;
		int id;
	public:
		Card(const char* image, int effect, int magnitude, int id);
		
		int getEffect();
		int getMagnitude();
		int getId();
};
