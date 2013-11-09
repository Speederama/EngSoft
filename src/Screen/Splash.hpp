# include "Screen.hpp"
# include "../Game/Data.hpp"


class Splash : public Screen {

public:

	// Constructor
	Splash(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			const Data& data);

	// Destructor
	~Splash(void);

	// Processes new events
	const bool process(void);

	// Draws contents to display
	void draw(void);

};
