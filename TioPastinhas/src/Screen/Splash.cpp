# include "Splash.hpp"


// Constructor
Splash::Splash(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		const Data& data) :
Screen(display, event, 1) {

	// Fonts
	_load_font("text", config::misc::font::dejavu, 25);

	// Background images
	_load_image("back", config::misc::image::splash);
	_create_image("cover", _width, _height);

	// Background sounds
	_load_sound("intro", config::misc::sound::intro);

}

// Destructor
Splash::~Splash(void) {
}

// Processes new events
const bool Splash::process(void) {

	static bool has_played(false);

	// Splash screen song 
	if (not has_played) {
		has_played = true;
		_sound["intro"]->play<Sound::NOREPEAT>();
	}

	// <ENTER> event
	if (_key.is_released(ALLEGRO_KEY_ENTER)) {
		_sound["intro"]->stop();
		return true;
	}

	return false;

}

// Draws contents to display
void Splash::draw(void) {

	static int alpha(255);

	++_counter;

	// Screen image
	Image::set_target(_display);
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);

	switch (_step) {
	case 0:

		alpha -= .005 * alpha;
		_image["cover"]->set_color(_palette, "black", alpha);
		_image["cover"]->draw<Image::NORMAL>(0, 0);

		if (alpha <= 0) ++_step;
		break;

	case 1:

		_font["text"]->draw<Font::CENTER>(_palette,
				((_counter % 30) > 15 ? "royalblue" : "green"),
				.5, .85,
				"Pressione <ENTER> para continuar");
	}

}
