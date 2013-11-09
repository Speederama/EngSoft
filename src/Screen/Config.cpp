# include <string>
# include <sstream>
# include "Config.hpp"


// Constructor
Config::Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data),
_avatar_selected(false),
_cur_avatar(0), _num_avatars(config::misc::avatar::count),
_user_process(-1), _username("") {

	// Fonts
	_load_font("text", config::misc::font::dejavu, 25);
	_load_font("18", config::misc::font::dejavu, 18);

	// Background images
	_load_image("back", config::misc::image::config);

	// Avatar images
	std::string id;
	std::stringstream ss;
	for (int i(0); i < _num_avatars; ++i) {
		ss.str(""), ss << i, id = ss.str();
		_load_image(id, config::misc::avatar::src + id + ".png");
	}

	// Buttons
	float inc(.07), leftpos(0), botpos(.72);
	_load_button<Button::PUSH>("prev", config::misc::button::left,
			leftpos + inc, botpos, 50, 50);
	_load_button<Button::TOGGLE>("mark", config::misc::button::tick,
			leftpos + 2 * inc, botpos, 50, 50);
	_load_button<Button::PUSH>("next", config::misc::button::right,
			leftpos + 3 * inc, botpos, 50, 50);

}

// Destructor
Config::~Config(void) {
}

// Processes new events
const bool Config::process(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;

	// Avatar selection
	_choose_avatar();
	return false;

}

// Draws contents to display
void Config::draw(void) {

	++_counter;
	Image::set_target(_display);

	// Background
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);

	// Avatar
	std::stringstream ss; ss << _cur_avatar;
	_image[ss.str()]->draw<Image::SCALED>(.054, .225, 273, 355);

	_font["18"]->draw<Font::LEFT>(_palette, "black",
			.295, .35, _username);

	_button["prev"]->draw();
	_button["mark"]->draw();
	_button["next"]->draw();

}

// Allows the user to choose an avatar
void Config::_choose_avatar(void) {

	// Validates user input data
	if (_button["mark"]->pressed()) _avatar_selected ^= true;
	if (_avatar_selected) {

		if (_username.empty() or _user_process == -1) {
			_avatar_selected = false, _button["mark"]->reset();
			al_show_native_message_box(_display,
					"Selecionar Personagem", "Aviso:",
					"você não selecionou um método de processo "
					"ou não inseriu um nome de jogador.",
					"OK", ALLEGRO_MESSAGEBOX_WARN);
		} else {
			return;
		}

	}

	// Change avatar picture back/forth
	if (_button["next"]->pressed()) {
		++_cur_avatar %= _num_avatars, _button["next"]->reset();
	} else if (_button["prev"]->pressed()) {
		if (--_cur_avatar < 0) _cur_avatar = _num_avatars - 1;
		_button["prev"]->reset();
	}

	// User name
	if (_event.type == ALLEGRO_EVENT_KEY_CHAR) {

		char l[5]; std::fill_n(l, 5, '\0');
		const int c(_event.keyboard.unichar);
		if (c >= 32) al_utf8_encode(l, c), _username += l;
		else if (_event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE
				and not _username.empty()) _username.pop_back();
		if (_username.size() > 30) _username.resize(30);

	}

}
