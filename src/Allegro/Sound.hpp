# include <allegro5/allegro.h>
# include <allegro5/allegro_audio.h>
# include <allegro5/allegro_acodec.h>
# include "Allegro.hpp"


class Allegro::Sound {

public:

	enum Mode {
		NOREPEAT
	};

	// Constructor
	inline Sound(const ALLEGRO_EVENT& event,
			const std::string& path) :
	_event(event), _path(path) {

		_sound = al_load_sample(path.c_str());
		if (_sound == NULL) config::error::load(path);

	}

	// Destructor
	inline ~Sound(void) {
		al_destroy_sample(_sound);
	}

	// Plays the sound
	template <int mode>
	inline void play(void) {

		ALLEGRO_PLAYMODE cur_mode;
		switch (mode) {
		case 0: cur_mode = ALLEGRO_PLAYMODE_ONCE; break;
		}

		al_play_sample(_sound, 1.0, 0.0, 1.0, cur_mode, &_sound_id);

	}

	// Stops the sound
	inline void stop(void) {
		al_stop_sample(&_sound_id);
	}

private:

	const std::string _path;

	ALLEGRO_SAMPLE *_sound;
	ALLEGRO_SAMPLE_ID _sound_id;
	const ALLEGRO_EVENT& _event;

};
