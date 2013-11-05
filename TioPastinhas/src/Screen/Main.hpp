# include "Screen.hpp"
# include "../Game/Data.hpp"


class Main : public Screen {

public:

	// Constructor
	Main(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~Main(void);

	// Draws contents to display
	const bool draw(void);

private:

	int _step;
	Data& _data;

};
