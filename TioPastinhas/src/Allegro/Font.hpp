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
			const std::string& path, const int& size) :
	_event(event), _path(path), _size(size) {

		_font = al_load_ttf_font(path.c_str(), size, 0);
		if (_font == NULL) config::error::load(path);

	}

	// Destructor
	inline ~Font(void) {

		al_destroy_font(_font);

	}

	// Draws the text given
	template <int align = 0, class P>
	inline void draw(P&& palette, const std::string& color, 
			const float& x, const float& y,
			const std::string& text) {

		al_draw_text(_font, palette(color),
				config::screen::width * x,
				config::screen::height * y,
				align, text.c_str());

	}

private:

	ALLEGRO_FONT *_font;
	const ALLEGRO_EVENT& _event;

	const int& _size;
	const std::string _path;

};
