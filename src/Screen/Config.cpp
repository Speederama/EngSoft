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
	_load_font("18", config::misc::font::dejavu, 18);
	_load_font("14", config::misc::font::dejavu, 14);

	// Background images
	_load_image("back", config::misc::image::config);
	_load_image("avatar_bg", config::misc::avatar::bg);

	// Avatar images
	std::string id;
	std::stringstream ss;
	for (int i(0); i < _num_avatars; ++i) {
		ss.str(""), ss << i, id = ss.str();
		_load_image(id, config::misc::avatar::src + id + ".png");
	}

	// Buttons
	_load_button<Button::PUSH>("prev", config::misc::button::left,
			.08, .72, 50, 50);
	_load_button<Button::PUSH>("next", config::misc::button::right,
			.2, .72, 50, 50);
	_load_button<Button::TOGGLE>("mark", config::misc::button::tick,
			.48, .85, 50, 50);

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

	// Avatars
	_display_avatars();

}

// Allows the user to choose an avatar
void Config::_choose_avatar(void) {

	// Validates user input data
	if (_button["mark"]->pressed()) _avatar_selected ^= true;
	if (_avatar_selected) {

		if (_username.empty()) {
			_avatar_selected = false, _button["mark"]->reset();
			al_show_native_message_box(_display,
					"Selecionar Personagem", "Aviso:",
					"você não selecionou um método de processo "
					"ou não inseriu um nome de jogador.",
					"OK", ALLEGRO_MESSAGEBOX_WARN);
		} else {

			std::stringstream ss;
			ss << config::misc::avatar::src << _cur_avatar;

			Allegro::Image *img(new Allegro::Image(_display, _event,
									ss.str() + ".png"));
			_data.player.push_back(new Player(_username,
							"Praxis", img));

			_username.clear(), _user_process = -1;

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
				and not _username.empty()) {
			_username.resize(_username.size() - 1);
		}

		if (_username.size() > 30) _username.resize(30);

	}

}

// Displays the current players
void Config::_display_avatars(void) {

	std::stringstream ss;
	for (int i(0); i < _data.player.size(); ++i) {

		// Avatar background
		_image["avatar_bg"]->draw<Image::SCALED>(.57,
				.225 + i * .18);

		// Player avatar
		_data.player[i]->_avatar->draw<Image::SCALED>(.583,
				.246 + i * .18, 79, 70);

		// Player name
		_font["14"]->draw<Font::LEFT>(_palette, "black",
				.705, .247 + i * .18, _data.player[i]->_name);

		// Player process
		_font["14"]->draw<Font::LEFT>(_palette, "black",
				.705, .282 + i * .18, _data.player[i]->_process);

		// Player companies
		ss.str(""), ss << _data.player[i]->_num_companies();
		_font["14"]->draw<Font::LEFT>(_palette, "black",
				.872, .282 + i * .18, ss.str());

		// Player resources
		ss.str(""), ss << _data.player[i]->_get_resources();
		_font["14"]->draw<Font::LEFT>(_palette, "black",
				.705, .317 + i * .18, ss.str());

		// Player points
		ss.str(""), ss << _data.player[i]->_get_points();
		_font["14"]->draw<Font::LEFT>(_palette, "black",
				.872, .317 + i * .18, ss.str());

	}

}
