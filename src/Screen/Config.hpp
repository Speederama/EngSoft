# include <string>
# include "Screen.hpp"
# include "../Game/Data.hpp"


class Config : public Screen {

public:

	// Constructor
	Config(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~Config(void);

	// Processes new events
	const bool process(void);

	// Draws contents to display
	void draw(void);

private:

	Data& _data;

	int _cur_avatar, _num_avatars;
	std::string _username, _user_process;

	// Allows the user to choose an avatar
	void _choose_avatar(void);

	// Displays the current players
	void _display_avatars(void);

};
