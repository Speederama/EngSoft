# include "Screen.hpp"
# include "../Game/Data.hpp"


class End : public Screen {

public:

	// Constructor
	End(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
			Data& data);

	// Destructor
	~End(void);

	// Processes new events
	const bool process(void);

	// Draws contents to display
	void draw(void);

private:
        void drawPodium(const std::vector<std::pair<double,int>>& playerPoints,
            int winnerId);
        void drawPlayerStatus(Player * player, double startX, double startY);
	Data& _data;
        double _angle;
        double _delta;

};
