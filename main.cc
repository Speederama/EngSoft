#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <list>
#include <cstdio>

#include "Game.h"

using namespace std;

int main()
{
	printf("Initializing Allegro...\n");
        if (!al_init())
        {
                fprintf(stderr, "failed to initialize allegro!\n");
                return EXIT_FAILURE;
        }
        al_init_native_dialog_addon();
        al_init_image_addon();
        al_init_primitives_addon();
        al_init_font_addon();
        al_init_ttf_addon();
        al_install_mouse();
        srand(time(NULL));

	printf("Showing configuration screen...\n");
	//TODO: Call configuration screen and get info regarding players and stuff

	list< pair<pair<const char*, const char*>, const char*> > infoPlayers;
	infoPlayers.push_back(pair<pair<const char*, const char*>, const char*>(pair<const char*, const char*>("João da Silva", "XP"), 
		"figuras/avatar.jpg"));
	infoPlayers.push_back(pair<pair<const char*, const char*>, const char*>(pair<const char*, const char*>("Maria Souza", "Scrum"), 
		"figuras/avatar.jpg"));
	infoPlayers.push_back(pair<pair<const char*, const char*>, const char*>(pair<const char*, const char*>("Antônio Alberto", "Praxis"), 
		"figuras/avatar.jpg"));
	infoPlayers.push_back(pair<pair<const char*, const char*>, const char*>(pair<const char*, const char*>("Clara Nunes", "Kanban"), 
		"figuras/avatar.jpg"));

	printf("Starting game...\n");
	Game game(infoPlayers, 5);
	game.startGame();

        return EXIT_SUCCESS;
}
