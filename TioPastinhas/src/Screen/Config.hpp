# include "Screen.hpp"
# include "../Game/Data.hpp"


class Config : public Screen {

public:

	// Constructor
	Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~Config(void);

	// Processes new events
	const bool process(void);

	// Draws contents to display
	void draw(void);

private:

	Data& _data;

	// Draws the background
	void _background();

};
