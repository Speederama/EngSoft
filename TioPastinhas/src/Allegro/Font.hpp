# include <allegro5/allegro.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_font.h>
# include "Allegro.hpp"


class Allegro::Font {

public:

	enum Alignment {
		CENTER = ALLEGRO_ALIGN_CENTER
	};

	// Constructor
	inline Font(const ALLEGRO_EVENT& event,
			const std::string& path, const int& size,
			const std::vector<std::string>& color,
			const int& timer = 0) :
	_i(0), _ticks(0), _timer(timer > 0 ? timer : 1),
	_event(event), _color(color) {

		_font = al_load_ttf_font(path.c_str(), size, 0);
		if (_font == NULL) config::error::load(path);
		if (_color.empty()) config::error::invalid("no text color");

	}

	// Destructor
	inline ~Font(void) {

		_color.clear();
		al_destroy_font(_font);

	}

	// Draws the text given
	template <int align = 0, class P>
	inline void draw(P&& palette,
			const float& x, const float& y,
			const std::string& text) {

		if (_event.type == ALLEGRO_EVENT_TIMER) {
			++_ticks %= _timer;
			_i = (_i + (not _ticks)) % _color.size();
		}

		al_draw_text(_font, palette(_color[_i]),
				config::screen::width * x,
				config::screen::height * y,
				align, text.c_str());

	}

private:

	int _i;
	int _ticks, _timer;

	ALLEGRO_FONT *_font;
	const ALLEGRO_EVENT& _event;
	std::vector<std::string> _color;

};
