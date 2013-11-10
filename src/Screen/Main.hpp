# include "Screen.hpp"
# include "../Game/Data.hpp"


class Main : public Screen {

public:

	// Constructor
	Main(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~Main(void);

	// Processes new events
	const bool process(void);

	// Draws contents to display
	void draw(void);

private:

	Data& _data;

	float _angle;
	int _time_to_stop, _time_rotating;
	bool _solve_roulette;

	void _buy_company(void);
	void _certify_company(void);
	void _resolve_roulette(void);
	void _apply_effect(int effect, int magnitude);

};
