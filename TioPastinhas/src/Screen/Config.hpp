# include "Screen.hpp"
# include "../Game/Data.hpp"


class Config : public Screen {

public:

	// Constructor
	Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~Config(void);

	// Draws contents to display
	const bool draw(void);

private:

	char _step;
	Data& _data;

	// Draws the background
	void _background();

};
