# include <allegro5/allegro.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_font.h>
# include "Allegro.hpp"


class Allegro::Image {

public:

	enum Mode {
		NORMAL,
		SCALED,
		ROTATED,
                SCALED_ROTATED
	};

	// Constructor -- create
	inline Image(ALLEGRO_DISPLAY *display,
			const ALLEGRO_EVENT& event,
			const int& width, const int& height) :
	_width(width), _height(height), _path(""),
	_display(display), _event(event) {

		_image = al_create_bitmap(width, height);
		if (_image == NULL) config::error::create("image");;

	}

	// Constructor -- load
	inline Image(ALLEGRO_DISPLAY *display,
			const ALLEGRO_EVENT& event,
			const std::string& path) :
	_width(0), _height(0), _path(path),
	_display(display), _event(event) {

		_image = al_load_bitmap(path.c_str());
		if (_image == NULL) config::error::load(path);

		_width = al_get_bitmap_width(_image);
		_height = al_get_bitmap_height(_image);

	}

	// Destructor
	inline ~Image(void) {
		al_destroy_bitmap(_image);
	}

	// Sets the output target
	inline static void set_target(ALLEGRO_DISPLAY *display) {
		al_set_target_bitmap(al_get_backbuffer(display));
	}

	// Sets the image color
	template <class P>
	inline void set_color(P&& palette, const std::string& color,
			const int& alpha = 255) {

		al_set_target_bitmap(_image);
		al_clear_to_color(palette(color, alpha));
		al_set_target_bitmap(al_get_backbuffer(_display));

	}

	// Draws the text given
	template <char mode, int flag = 0>
	inline void draw(const float& x, const float& y,
			int width = -1, int height = -1, 
			float angle = 0.0, const float& xscale = 1.,
                        const float& yscale = 1.) const {

		if (width == -1) width = _width;
		if (height == -1) height = _height;

		switch (mode) {
		case 0:
			al_draw_bitmap(_image,
					config::screen::width * x,
					config::screen::height * y,
					flag);
			break;
		case 1:
			al_draw_scaled_bitmap(_image, 0, 0, _width, _height,
					config::screen::width * x,
					config::screen::height * y,
					width, height,
					flag);
			break;
		case 2:
			al_draw_rotated_bitmap(_image, width, 
				height, config::screen::width * x, 
				config::screen::height * y, angle, 
				flag);
			break;
                case 3:
                        al_draw_scaled_rotated_bitmap(_image, 
                            al_get_bitmap_width(_image)/2.,
                            al_get_bitmap_height(_image)/2.,
                            //width/2.,
                            //height/.2, 
                            config::screen::width * x,
                            config::screen::height * y, xscale, yscale,
                            angle, flag);
                            
		}

	}

private:

	int _width, _height;
	const std::string _path;

	ALLEGRO_BITMAP *_image;
	ALLEGRO_DISPLAY *_display;
	const ALLEGRO_EVENT& _event;

};
