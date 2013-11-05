# include <vector>
# include <iostream>
# include "Data.hpp"
# include "../Screen/Screen.hpp"
# include "../Allegro/Allegro.hpp"


class Game {

public:

	// Constructor
	Game(void);

	// Destructor
	~Game(void);

	// Game loop
	void run(void);

private:

	const float _fps;
	const int _width, _height;

	Data _data;
	Screen *_screen;

	int _step;
	ALLEGRO_TIMER *_timer;
	ALLEGRO_DISPLAY *_display;

	ALLEGRO_EVENT _event;
	ALLEGRO_EVENT_QUEUE * _queue;

	// Updates the current screen
	template <class T>
	inline const bool _update() {

		if (_screen == NULL) {
			_screen = new T(_display, _event, _data);
		}

		if (_screen->draw()) delete _screen, _screen = NULL;
		return (_screen == NULL);

	}

};
