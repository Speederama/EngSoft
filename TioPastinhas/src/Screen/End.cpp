# include "End.hpp"


// Constructor
End::End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data), _step(0) {

	// Fonts
	_load_font("main", config::misc::font::dejavu,
			25, {"white"});

}

// Destructor
End::~End(void) {
}

// Draws contents to display
const bool End::draw(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;

	_font["main"]->draw<Font::CENTER>(_palette, .5, .85,
			"THE END!!!\nTHE GROUP...\nWanna quit? press <ESC>");
	return false;

}
