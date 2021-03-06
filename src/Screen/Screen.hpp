# ifndef SCREEN_HPP
# define SCREEN_HPP

# include <string>
# include <unordered_map>
# include "../Allegro/Allegro.hpp"


class Screen : public Allegro {

public:

	// Constructor
	Screen(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT &event,
			const int& num_samples = 0);

	// Destructor
	virtual ~Screen(void);

	// Processes new events
	virtual const bool process(void);

	// Draws contents to display
	virtual void draw(void);

protected:

	bool _finished;

	int _step;
	uint64_t _counter;

	ALLEGRO_EVENT& _event;
	ALLEGRO_DISPLAY *_display;

	Palette _palette;
	std::unordered_map<std::string, Font *> _font;
	std::unordered_map<std::string, Image *> _image;
	std::unordered_map<std::string, Sound *> _sound;

	Keyboard _key;
	std::unordered_map<std::string, Button *> _button;

	// Loads a font
	void _load_font(const std::string& id,
			const std::string& path, const int& size);

	// Creates an image
	void _create_image(const std::string& id,
			const int& width, const int& height);

	// Loads an image
	void _load_image(const std::string& id, const std::string& path);

	// Loads a sound
	void _load_sound(const std::string& id, const std::string& path);

	// Loads a button
	template <char type>
	void _load_button(const std::string& id, const std::string& path,
			const float& x, const float& y,
			const float& dx, const float& dy) {

		if (_button.find(id) != _button.end()) {
			config::error::load("button[" + id + "] already taken");
		}
		_button[id] = new Button(type, _event, path, x, y, dx, dy);

	}

};

# endif
