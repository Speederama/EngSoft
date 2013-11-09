# include <vector>
# include <allegro5/allegro.h>
# include "Allegro.hpp"


class Allegro::Button {

public:

	enum Type {
		PUSH, LOCK, TOGGLE
	};

	// Constructor
	inline Button(const char& btn_type, const ALLEGRO_EVENT& event,
			const std::string& path, const float& x, const float& y,
			const float& dx = -1, const float& dy = -1) :
	_event(event), _path(path),
	_x(x), _y(y), _dx(dx), _dy(dy), _width(0), _height(0),
	_link(NULL), _visited(NULL), _hover(NULL), _cur(NULL),
	_clicked(false), _moved(false),
	_was_over(false), _is_over(false),
	_was_pressed(false), _is_pressed(false) {

		switch (btn_type) {
		case 0: _hold = false, _toggle = false; break;
		case 1: _hold = true, _toggle = false; break;
		case 2: _hold = true, _toggle = true; break;
		default: config::error::invalid("unknown button type");
		}

		_load_image(_link, path + "_LINK.png");
		_load_image(_visited, path + "_VISITED.png");
		_load_image(_hover, path + "_HOVER.png");

		_cur = _link;
		_x *= config::screen::width, _y *= config::screen::height;

	}

	// Destructor
	inline ~Button(void) {

		al_destroy_bitmap(_link);
		al_destroy_bitmap(_visited);
		al_destroy_bitmap(_hover);

	}

	// Draws the button
	inline void draw(void) {

		al_draw_scaled_bitmap(_cur, 0, 0, _width, _height,
				_x, _y, _dx, _dy, 0);

	}

	// Resets the button state
	inline void reset(void) {

		_cur = _link;
		_clicked = false, _moved = false;
		_was_over = false, _is_over = false;
		_was_pressed = false, _is_pressed = false;

	}

	// Checks whether the button is pressed
	inline const bool pressed(void) {

		if (_cur == NULL) _cur = _link;
		else if (not _update()) return false;

		if (not _was_pressed and not _was_over) {

			if (_is_over) _cur = (_is_pressed ? _visited : _hover);

		} else if (not _was_pressed) {

			if (not _is_over) _cur = _link;
			else if (_is_pressed) _cur = _visited;

		} else if (_toggle and _is_pressed
				and _clicked and _is_over) {

			_is_pressed = false, _cur = _hover;

		} else if (not _hold and not _toggle and not _is_pressed) {

			_cur = (_is_over ? _hover : _link);

		}

		return ((not _was_pressed and _is_pressed)
				or (_toggle and (_was_pressed != _is_pressed)));

	}

private:

	const std::string _path;
	const ALLEGRO_EVENT &_event;

	float _x, _y, _dx, _dy, _width, _height;
	ALLEGRO_BITMAP *_cur, *_link, *_visited, *_hover;

	bool _hold, _toggle, _clicked, _moved;
	bool _was_over, _is_over, _was_pressed, _is_pressed;

	// Loads the button image
	inline void _load_image(ALLEGRO_BITMAP *& image,
			const std::string& path) {

		image = al_load_bitmap(path.c_str());
		if (image == NULL) config::error::load(path);

		_width = al_get_bitmap_width(image);
		_height = al_get_bitmap_height(image);

		_dx = (_dx != -1 ? _dx : _width);
		_dy = (_dy != -1 ? _dy : _height);

	}

	// Checks for mouse activity over button -- returns true
	// if any change has been detected
	inline const bool _update(void) {

		const float x(_event.mouse.x), y(_event.mouse.y);
		_moved = (_event.type == ALLEGRO_EVENT_MOUSE_AXES);
		_clicked = (_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);

		if (not _moved and not _clicked) return false;

		_was_over = _is_over;
		_is_over = (_x <= x and x <= (_x + _dx)
				and _y <= y and y <= (_y + _dy));

		_was_pressed = _is_pressed;
		_is_pressed = ((_is_over and _clicked)
				or (_hold and _is_pressed));

		return true;

	}

};
