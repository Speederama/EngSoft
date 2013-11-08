# include "Config.hpp"


// Constructor
Config::Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data) {

	// Background images
	_load_image("back", config::misc::image::config);
	_create_image("cover", .95 * _width, .9 * _height);
	_image["cover"]->set_color(_palette, "black", 200);

	// Buttons
	_load_button<Button::PUSH>("add", config::misc::button::add,
			(.85 * _width), (.85 * _height), 80, 80);
	_load_button<Button::LOCK>("sub", config::misc::button::add,
			(.80 * _width), (.85 * _height), 80, 80);
	_load_button<Button::TOGGLE>("mul", config::misc::button::add,
			(.75 * _width), (.85 * _height), 80, 80);

}

// Destructor
Config::~Config(void) {
}

// Processes new events
const bool Config::process(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;
	return false;

}

// Draws contents to display
void Config::draw(void) {

	++_counter;

	switch (_step) {
	case 0: _background(); break;
	}

}

// Draws the background
void Config::_background(void) {

	Image::set_target(_display);
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);
	_image["cover"]->draw<Image::NORMAL>(.025, .05);

	_button["add"]->draw();
	_button["sub"]->draw();
	_button["mul"]->draw();

}
