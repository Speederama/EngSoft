# include <vector>
# include <allegro5/allegro.h>
# include <allegro5/keyboard.h>
# include "Allegro.hpp"


class Allegro::Keyboard {

public:

	// Constructor
	inline Keyboard(const ALLEGRO_EVENT& event) :
	_event(event) {
	}

	// Destructor
	inline ~Keyboard(void) {
	}

	// Checks whether the given key is pressed
	inline const bool is_pressed(const int& key) {
		if (_event.type != ALLEGRO_EVENT_KEY_DOWN) return false;
		return (_event.keyboard.keycode == key);
	}

	// Checks whether one of the given keys is pressed
	inline const bool is_pressed(const std::vector<int>& key) {

		if (_event.type != ALLEGRO_EVENT_KEY_DOWN) return false;
		for (int i(0); i < key.size(); ++i) {
			if (_event.keyboard.keycode == key[i]) return true;
		}

		return false;

	}

	// Checks whether the given key is released
	inline const bool is_released(const int& key) {
		if (_event.type != ALLEGRO_EVENT_KEY_UP) return false;
		return (_event.keyboard.keycode == key);
	}

	// Checks whether one of the given keys is released
	inline const bool is_released(const std::vector<int>& key) {

		if (_event.type != ALLEGRO_EVENT_KEY_UP) return false;
		for (int i(0); i < key.size(); ++i) {
			if (_event.keyboard.keycode == key[i]) return true;
		}

		return false;

	}

private:

	const ALLEGRO_EVENT &_event;

};
