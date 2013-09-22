#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define HOR_LINE_INFO_PLAYER_HEIGHT 0.65
#define HOR_LINE_ROUNDS_HEIGHT 0.05
#define VERT_LINE_PLAYERS_WIDTH 0.7
#define VERT_LINE_AVATAR_WIDTH 0.15
#define INVENTORY_HEIGHT_POS 0.73
#define INVENTORY_WIDTH_POS 0.65
#define INVENTORY_HEIGHT 0.25
#define INVENTORY_WIDTH 0.3
#define INVENTORY_TITLE_WIDTH 0.75
#define INVENTORY_TITLE_HEIGHT 0.68

class MainScreen
{
	private:
		ALLEGRO_DISPLAY* display;
		ALLEGRO_DISPLAY_MODE disp_data;

		int height, width;

		int drawRoullete(float angle);
		int drawLegendArrow();
		int drawButtons();
		int drawAvatar(const char* filename);
		int drawPlayerInfo(const char* playerName, const char* methodology, int currentPoints, long currentMoney);
		int drawOtherPlayers();
		int drawRounds(int roundNumber, int totalRounds);

	public:
		MainScreen();
		int drawScreen();
		void rotateRoullete();
};
