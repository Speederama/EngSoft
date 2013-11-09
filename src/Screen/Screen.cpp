# include <string>
# include <allegro5/allegro.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_font.h>
# include "../Config/Config.hpp"
# include "Screen.hpp"


// Constructor
Screen::Screen(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		const int& num_samples) :
_finished(false), _step(0), _counter(0),
_key(event), _event(event), _display(display) {
	al_reserve_samples(num_samples);
}

// Destructor
Screen::~Screen(void) {

	for (auto it(_font.begin()), e(_font.end()); it != e; ++it) {
		delete it->second;
	}

	for (auto it(_image.begin()), e(_image.end()); it != e; ++it) {
		delete it->second;
	}

	for (auto it(_sound.begin()), e(_sound.end()); it != e; ++it) {
		delete it->second;
	}

	for (auto it(_button.begin()), e(_button.end()); it != e; ++it) {
		delete it->second;
	}

	_font.clear();
	_image.clear();
	_sound.clear();
	_button.clear();

	Image::set_target(_display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

}

// Processes new events
const bool Screen::process() {
}

// Draws screen contents
void Screen::draw() {
}

// Loads a font
void Screen::_load_font(const std::string& id,
		const std::string& path, const int& size) {

	if (_font.find(id) != _font.end()) {
		config::error::load("font[" + id + "] already taken");
	}
	_font[id] = new Font(_event, path, size);

}

// Creates an image
void Screen::_create_image(const std::string& id,
		const int& width, const int& height) {

	if (_image.find(id) != _image.end()) {
		config::error::load("image[" + id + "] already taken");
	}
	_image[id] = new Image(_display, _event, width, height);

}

// Loads an image
void Screen::_load_image(const std::string& id,
		const std::string& path) {

	if (_image.find(id) != _image.end()) {
		config::error::load("image[" + id + "] already taken");
	}
	_image[id] = new Image(_display, _event, path);

}

// Loads a sound
void Screen::_load_sound(const std::string& id,
		const std::string& path) {

	if (_image.find(id) != _image.end()) {
		config::error::load("sound[" + id + "] already taken");
	}
	_sound[id] = new Sound(_event, path);

}
