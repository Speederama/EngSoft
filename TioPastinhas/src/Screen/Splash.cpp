# include "Splash.hpp"


// Constructor
Splash::Splash(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		const Data& data) :
Screen(display, event, 1) {

	// Fonts
	_load_font("text", config::misc::font::dejavu,
			25, {"black", "white"});

	// Background images
	_load_image("back", config::misc::image::splash);
	_create_image("cover", _width, _height);

	// Background sounds
	_load_sound("intro", config::misc::sound::intro);

}

// Destructor
Splash::~Splash(void) {
}

// Draws contents to display
const bool Splash::draw(void) {

	static int alpha(255);
	static bool has_played(false);
	static char step(0), color(0), counter(0);

	// Splash screen song 
	if (not has_played) {
		has_played = true;
		_sound["intro"]->play<Sound::NOREPEAT>();
	}

	// <ENTER> event
	if (step and _key.is_released(ALLEGRO_KEY_ENTER)) {
		_sound["intro"]->stop();
		return true;
	}

	// Screen image
	Image::set_target(_display);
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);

	switch (step) {
	case 0:
		if (_event.type != ALLEGRO_EVENT_TIMER) break;
		++counter %= 3, alpha -= ((not counter) * 0.05 * alpha);
		step = (alpha <= 0 ? step + 1 : step);
		_image["cover"]->set_color(_palette, "black", alpha);
		Image::set_target(_display);
		_image["cover"]->draw<Image::NORMAL>(1, 1);
		break;
	case 1:
		_font["text"]->draw<Font::CENTER>(_palette, .5, .85,
				"Pressione <ENTER> para continuar");
	}

	return false;

}
