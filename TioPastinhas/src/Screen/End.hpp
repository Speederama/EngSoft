# include "Screen.hpp"
# include "../Game/Data.hpp"


class End : public Screen {

public:

	// Constructor
	End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~End(void);

	// Draws contents to display
	const bool draw(void);

private:

	char _step;
	Data& _data;

};
