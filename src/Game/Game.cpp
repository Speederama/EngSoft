# include <vector>
# include <iostream>
# include "Game.hpp"
# include "../Screen/Splash.hpp"
# include "../Screen/Config.hpp"
# include "../Screen/Main.hpp"
# include "../Screen/End.hpp"


// Constructor
Game::Game(void) :
_fps(config::screen::fps),
_width(config::screen::width),
_height(config::screen::height),
_screen(NULL), _timer(NULL), _display(NULL), _queue(NULL),
_step(0) {

	// Allegro5 initialization
	if (not al_init()) config::error::init();

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_native_dialog_addon();

	al_install_audio();
	al_install_mouse();
	al_install_keyboard();

	// Display initialization
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	_display = al_create_display(_width, _height);

	if (_display == NULL) config::error::display();
	al_set_window_title(_display, config::data::title.c_str());

	// Timer and events initialization
	_timer = al_create_timer(1 / _fps);
	_queue = al_create_event_queue();

	al_register_event_source(_queue,
			al_get_timer_event_source(_timer));
	al_register_event_source(_queue,
			al_get_display_event_source(_display));
	al_register_event_source(_queue, al_get_mouse_event_source());
	al_register_event_source(_queue, al_get_keyboard_event_source());

}

// Destructor
Game::~Game(void) {

	delete _screen;

	al_destroy_timer(_timer);
	al_destroy_display(_display);
	al_destroy_event_queue(_queue);

}

// Game loop
void Game::run(void) {

	al_start_timer(_timer);
	do {

		al_wait_for_event(_queue, &_event);
		do {

			if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return;

			switch (_step) {
			case 0:
				++_step;
				Card::loader(config::data::path::card,
				 		_data.card);
				Question::loader(config::data::path::question,
						_data.question);
				break;
			case 1:
				if (_update<Splash>()) ++_step;
				break;
			case 2:
				if (_update<Config>()) ++_step;
				break;
			case 3:
				if (_update<Main>()) ++_step;
				if (_event.type == ALLEGRO_EVENT_TIMER)
					al_flush_event_queue(_queue);
				break;
			case 4:
				if (_update<End>()) ++_step;
				break;
			case 5:
				return;
			}

		} while (al_get_next_event(_queue, &_event));

	} while (true);

}
