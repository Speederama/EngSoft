# include <string>
# include <sstream>
# include "Config.hpp"


// Constructor
Config::Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data),
_cur_avatar(0), _num_avatars(config::misc::avatar::count),
_user_process(""), _username("") {

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

	// Avatar selection buttons
	_load_button<Button::PUSH>("prev", config::misc::button::left,
			.08, .72, 50, 50);
	_load_button<Button::PUSH>("next", config::misc::button::right,
			.2, .72, 50, 50);
	_load_button<Button::PUSH>("mark", config::misc::button::tick,
			.48, .85, 50, 50);

	// Menu buttons
	float xpos(.322), ypos(.38);
	for (int i(0); i < config::game::num_methods; ++i) {
		_load_button<Button::LOCK>(config::game::method[i],
				config::misc::button::menu,
				xpos, ypos += .07, 205, 50);
	}

	// Play button
	_load_button<Button::PUSH>("play", config::misc::button::play,
			.865, .92, 100, 50);

	// Pre-defined data
	_data.num_rounds = 5, _data.cur_round = 1;

}

// Destructor
Config::~Config(void) {
}

// Processes new events
const bool Config::process(void) {

	// Game start
	if (_button["play"]->pressed()) {

		if (_data.player.empty()) {
			al_show_native_message_box(_display,
					"Selecionar Personagem", "Aviso:",
					"você precisa selecionar ao menos um jogador.",
					"OK", ALLEGRO_MESSAGEBOX_WARN);
		} else return true;

	}

	// Avatar selection
	_choose_avatar();
	return false;

}

// Draws contents to display
void Config::draw(void) {

	Image::set_target(_display);
	const int c(++_counter % _fps);

	// Background
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);

	// Avatar
	std::stringstream ss; ss << _cur_avatar;
	_image[ss.str()]->draw<Image::SCALED>(.054, .225, 273, 355);

	// Text input
	_font["18"]->draw<Font::LEFT>(_palette, "black",
			.295, .345, _username + (c > _fps / 2 ? "|" : ""));

	// Avatars
	_button["prev"]->draw();
	_button["mark"]->draw();
	_button["next"]->draw();
	_display_avatars();

	// Management methods
	float xpos(.396), ypos(.396);
	for (int i(0); i < config::game::num_methods; ++i) {
		_button[config::game::method[i]]->draw();
		_font["18"]->draw<Font::CENTER>(_palette, "white",
				xpos, ypos += .07, config::game::method[i]);
	}

	// Play button
	_button["play"]->draw();

}

// Allows the user to choose an avatar
void Config::_choose_avatar(void) {

	// Validates user input data
	if (_button["mark"]->pressed()) {

		if (_username.empty() or _user_process.empty()) {

			al_show_native_message_box(_display,
					"Selecionar Personagem", "Aviso:",
					"você não selecionou um método de processo "
					"ou não inseriu um nome de jogador.",
					"OK", ALLEGRO_MESSAGEBOX_WARN);

		} else if (_data.player.size() ==
				config::game::max_players) {

			al_show_native_message_box(_display,
					"Selecionar Personagem", "Erro:",
					"a versão atual de Roda o Software ® "
					"não suporta mais de quatro jogaddores.",
					"OK", ALLEGRO_MESSAGEBOX_ERROR);

		} else {

			std::stringstream ss;
			ss << config::misc::avatar::src << _cur_avatar;

			Allegro::Image *img(new Allegro::Image(_display, _event,
									ss.str() + ".png"));
			_data.player.push_back(new Player(_username,
							_user_process, img));

			// Resetting user data
			if (not _user_process.empty()) {
				_button[_user_process]->reset();
			}
			_username.clear(), _user_process.clear();

		}

	}

	// Select the management process
	for (int i(0); i < config::game::num_methods; ++i) {

		if (_button[config::game::method[i]]->pressed()) {

			if (not _user_process.empty()) {
				_button[_user_process]->reset();
			}

			_user_process = config::game::method[i];
			break;

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
