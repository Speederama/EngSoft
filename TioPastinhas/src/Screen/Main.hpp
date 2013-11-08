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
	bool _rotating;

	void _buy_company(void);

	void _certify_company(void);

};
