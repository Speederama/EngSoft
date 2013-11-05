# ifndef ALLEGRO_HPP
# define ALLEGRO_HPP

# include <string>
# include <vector>
# include <unordered_map>
# include <allegro5/allegro.h>
# include <allegro5/allegro_image.h>
# include <allegro5/allegro_primitives.h>
# include <allegro5/allegro_native_dialog.h>
# include "../Config/Config.hpp"


class Allegro {

public:

	// Miscellaneous interface
	class Font;
	class Image;
	class Sound;

	// Mouse interface
	class Button;

	// Keyboard interface
	class Keyboard;

	// Colors interface
	class Palette {

	public:

		// Constructor
		Palette(void);

		// Destructor
		~Palette(void);

		// Functor
		ALLEGRO_COLOR operator()(const std::string& color,
				const int& alpha = 255);

	private:

		std::unordered_map<std::string, std::vector<int> > _color;

	};

protected:

	const int _fps, _width, _height;

	// Constructor
	Allegro(void) :
	_fps(config::screen::fps),
	_width(config::screen::width),
	_height(config::screen::height) {
	}

	// Destructor
	~Allegro(void) {
	}

};

// Constructor
inline Allegro::Palette::Palette(void) {

	// Available colors
	_color["black"] = {0, 0, 0};
	_color["white"] = {255, 255, 255};

}

// Destructor
inline Allegro::Palette::~Palette(void) {

	_color.clear();

}

// Functor
inline ALLEGRO_COLOR Allegro::Palette::operator()(
		const std::string& color, const int& alpha) {

	if (_color.find(color) == _color.end()) {
		config::error::invalid("unknown color " + color);
	}

	int *rgb(&_color[color][0]);
	return al_map_rgba(rgb[0], rgb[1], rgb[2], alpha);

}

# include "Font.hpp"
# include "Image.hpp"
# include "Sound.hpp"
# include "Button.hpp"
# include "Keyboard.hpp"

# endif
