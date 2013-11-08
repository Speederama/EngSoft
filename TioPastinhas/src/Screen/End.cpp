# include "End.hpp"


// Constructor
End::End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data) {

	// Fonts
	_load_font("main", config::misc::font::dejavu, 25);

}

// Destructor
End::~End(void) {
}

// Processes new events
const bool End::process(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;
	return false;

}

// Draws contents to display
void End::draw(void) {

	_font["main"]->draw<Font::CENTER>(_palette, "white",
			.5, .85,
			"THE END!!!\nTHE GROUP...\nWanna quit? press <ESC>");

}
