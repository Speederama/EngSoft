#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include <list>
#include <string>

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
		ALLEGRO_BITMAP* imageRoullete;

		int height, width;
		float angle;

		std::string fileImageAvatar, namePlayer, methodologyPlayer;
		int pointsPlayer, resourcePlayer, numRound, maxRounds;
		std::list< std::pair<const char*, int> > otherPlayers, companiesPlayer;

		int rotateRoullete();
		int confirmPurchase();
		int confirmCertification();

		int showQuestion(bool specific);
		int showCard(bool lucky);

		int drawScreen();
		int drawBackground();
		int drawLinesText();
		int drawRoullete(float angle);
		int drawLegendArrow();
		int drawButtons();
		int drawAvatar(const char* filename);
		int drawPlayerInfo(const char* playerName, const char* methodology, int currentPoints, int currentMoney, 
			const std::list< std::pair<const char*, int> >& companies);
		int drawOtherPlayers(const std::list< std::pair<const char*, int> >& otherPlayers);
		int drawRounds(int roundNumber, int totalRounds);

	public:
		MainScreen();
		int drawScreen(const char* fileImageAvatar, int numRound, int maxRounds, const char* namePlayer, 
			const char* methodologyPlayer, int points, int resources, const std::list< std::pair<const char*, int> >& companiesPlayer, 
			const std::list< std::pair<const char*, int> >& otherPlayers);
		int waitForEvent();
		void showMessage(const char* caption, const char* header, const char* text, bool error);
};
