#include <stdio.h>

#include "MainScreen.h"

MainScreen::MainScreen()
{
	display = NULL;
	height = 0;
	width = 0;
}

void MainScreen::rotateRoullete()
{
	float angle = 3.1415 / 10;
	while(1)
	{
		drawRoullete(angle);
		al_rest(1);
		angle += 3.1415 / 10;
		al_flip_display();
	}
}

int MainScreen::drawScreen()
{
	ALLEGRO_BITMAP *lineHorizontal = NULL;
	ALLEGRO_BITMAP *lineVertPlayers = NULL;
	ALLEGRO_BITMAP *lineVertAvatar = NULL;
	ALLEGRO_BITMAP *lineVertInventory = NULL;
	ALLEGRO_BITMAP *lineHorInventory = NULL;

	ALLEGRO_FONT *fontRounds = NULL;
	ALLEGRO_FONT *fontInvent = NULL;

	//al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_get_display_mode(0, &disp_data);

	width = (int) (0.9 * disp_data.width);
	height = (int) (0.85 * disp_data.height);
   	display = al_create_display(width, height);
	if(!display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255));

	ALLEGRO_BITMAP *imageBack = al_load_bitmap("figuras/background.jpg");
	al_draw_scaled_bitmap(imageBack, 0, 0, al_get_bitmap_width(imageBack), al_get_bitmap_height(imageBack), 0, 0, width, height, 0);

	lineHorizontal = al_create_bitmap(width, 5);
	al_set_target_bitmap(lineHorizontal);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	lineVertPlayers = al_create_bitmap(5, height * (HOR_LINE_INFO_PLAYER_HEIGHT - HOR_LINE_ROUNDS_HEIGHT) + 5);
	al_set_target_bitmap(lineVertPlayers);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	lineVertAvatar = al_create_bitmap(5, height * (1 - HOR_LINE_INFO_PLAYER_HEIGHT) + 5);
	al_set_target_bitmap(lineVertAvatar);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	lineVertInventory = al_create_bitmap(5, height * INVENTORY_HEIGHT);
	al_set_target_bitmap(lineVertInventory);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	lineHorInventory = al_create_bitmap(INVENTORY_WIDTH * width + 5, 5);
	al_set_target_bitmap(lineHorInventory);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(lineHorizontal, 0, height * HOR_LINE_INFO_PLAYER_HEIGHT, 0);
	al_draw_bitmap(lineHorizontal, 0, height * HOR_LINE_ROUNDS_HEIGHT, 0);
	al_draw_bitmap(lineVertPlayers, VERT_LINE_PLAYERS_WIDTH * width, height * HOR_LINE_ROUNDS_HEIGHT, 0);
	al_draw_bitmap(lineVertAvatar, VERT_LINE_AVATAR_WIDTH * width, height * HOR_LINE_INFO_PLAYER_HEIGHT, 0);

	al_draw_bitmap(lineVertInventory, INVENTORY_WIDTH_POS * width, height * INVENTORY_HEIGHT_POS, 0);
	al_draw_bitmap(lineVertInventory, (INVENTORY_WIDTH_POS + INVENTORY_WIDTH) * width, height * INVENTORY_HEIGHT_POS, 0);
	al_draw_bitmap(lineHorInventory, INVENTORY_WIDTH_POS * width, height * INVENTORY_HEIGHT_POS, 0);
	al_draw_bitmap(lineHorInventory, INVENTORY_WIDTH_POS * width, height * (INVENTORY_HEIGHT_POS + INVENTORY_HEIGHT), 0);


	fontInvent = al_load_ttf_font("DejaVuSans.ttf", 25, 0);
	al_draw_text(fontInvent, al_map_rgb(0, 0, 0), INVENTORY_TITLE_WIDTH * width, INVENTORY_TITLE_HEIGHT * height, 0, "Inventário");

	drawRoullete(0);
	drawLegendArrow();
	drawButtons();

	drawAvatar("figuras/avatar.jpg");
	drawRounds(1, 10);
	drawOtherPlayers();
	drawPlayerInfo("João da Silva", "XP", 160, 1000000);

	al_flip_display();

	al_rest(100);
}

int MainScreen::drawButtons()
{
	ALLEGRO_BITMAP *imageButtonBuy = al_load_bitmap("figuras/botao_compra.png");
	al_draw_scaled_bitmap(imageButtonBuy, 0, 0, al_get_bitmap_width(imageButtonBuy), al_get_bitmap_height(imageButtonBuy), VERT_LINE_PLAYERS_WIDTH * width - 200, 100, 200, 150, 0);
	ALLEGRO_BITMAP *imageButtonCert = al_load_bitmap("figuras/botao_certifica.png");
	al_draw_scaled_bitmap(imageButtonCert, 0, 0, al_get_bitmap_width(imageButtonCert), al_get_bitmap_height(imageButtonCert), VERT_LINE_PLAYERS_WIDTH * width - 200, 200, 200, 150, 0);
}

int MainScreen::drawLegendArrow()
{
	ALLEGRO_BITMAP *imageLegend = al_load_bitmap("figuras/legenda.png");
	al_draw_bitmap(imageLegend, 0, 0, 0);

	ALLEGRO_BITMAP *imageArrow = al_load_bitmap("figuras/seta.png");
	al_draw_scaled_bitmap(imageArrow, 0, 0, al_get_bitmap_width(imageArrow), al_get_bitmap_height(imageArrow), 0.35 * width - 25, 0.55 * height, 50, 50, 0);
}

int MainScreen::drawRoullete(float angle)
{
	ALLEGRO_BITMAP *imageRoullete = al_load_bitmap("figuras/roleta.png");
	int heightImage = al_get_bitmap_height(imageRoullete);
	int widthImage = al_get_bitmap_width(imageRoullete);
	//al_draw_rotated_bitmap(imageRoullete, widthImage / 2, heightImage / 2, (VERT_LINE_PLAYERS_WIDTH / 2) * width,
	//	((HOR_LINE_INFO_PLAYER_HEIGHT - HOR_LINE_ROUNDS_HEIGHT) / 2 + HOR_LINE_ROUNDS_HEIGHT) * height, angle, 0);
	al_draw_rotated_bitmap(imageRoullete, 254, 232, (VERT_LINE_PLAYERS_WIDTH / 2) * width,
		((HOR_LINE_INFO_PLAYER_HEIGHT - HOR_LINE_ROUNDS_HEIGHT) / 2 + HOR_LINE_ROUNDS_HEIGHT) * height, angle, 0);
}

int MainScreen::drawRounds(int roundNumber, int totalRounds)
{
	ALLEGRO_FONT *fontRounds = al_load_ttf_font("DejaVuSans.ttf", 30, 0);
	char rounds[1024];
	sprintf(rounds, "Rodada #%d de %d", roundNumber, totalRounds);
	al_draw_text(fontRounds, al_map_rgb(0, 0, 0), 0.005 * width, 0.005 * height, 0, rounds);
}

int MainScreen::drawOtherPlayers()
{
	ALLEGRO_FONT *fontOtherPlayers = al_load_ttf_font("DejaVuSans.ttf", 15, 0);
	al_draw_text(fontOtherPlayers, al_map_rgb(0, 0, 0), 0.76 * width, 0.1 * height, 0, "Maria Souza - Pontuação: 210");
	al_draw_text(fontOtherPlayers, al_map_rgb(0, 0, 0), 0.76 * width, 0.2 * height, 0, "José Antônio - Pontuação: 115");	
}

int MainScreen::drawPlayerInfo(const char* playerName, const char* methodology, int currentPoints, long currentMoney)
{
	ALLEGRO_FONT *fontInfoPlayer = al_load_ttf_font("DejaVuSans.ttf", 15, 0);
	char name[1024];
	sprintf(name, "Nome: %s", playerName);
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), (VERT_LINE_AVATAR_WIDTH + 0.02) * width,
		(HOR_LINE_INFO_PLAYER_HEIGHT + 0.05) * height, 0, name);
	char method[1024];
	sprintf(method, "Metodologia: %s", methodology);
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), (VERT_LINE_AVATAR_WIDTH + 0.02) * width, 
		(HOR_LINE_INFO_PLAYER_HEIGHT + 0.10) * height, 0, method);
	char points[1024];
	sprintf(points, "Pontuação: %d", currentPoints);
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), (VERT_LINE_AVATAR_WIDTH + 0.02) * width,
		(HOR_LINE_INFO_PLAYER_HEIGHT + 0.15) * height, 0, points);
	char resource[1024];
	sprintf(resource, "Recursos: R$ %ld", currentMoney);
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), (VERT_LINE_AVATAR_WIDTH + 0.02) * width,
		(HOR_LINE_INFO_PLAYER_HEIGHT + 0.20) * height, 0, resource);

	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), 0.67 * width, 0.75 * height, 0, "Empresa 1 - CMMI 3");
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), 0.81 * width, 0.75 * height, 0, "Empresa 2 - CMMI 5");
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), 0.67 * width, 0.8 * height, 0, "Empresa 3 - CMMI 1");
}

int MainScreen::drawAvatar(const char* filename)
{
	ALLEGRO_BITMAP *imageAvatar = NULL;
	imageAvatar = al_load_bitmap(filename);
	if (imageAvatar == NULL)
	{
		fprintf(stderr, "failed to load image file %s!\n", filename);
		return -1;
	}

	int originalHeight = al_get_bitmap_height(imageAvatar);
	int originalWidth = al_get_bitmap_width(imageAvatar);
	int widthAvailable = width * VERT_LINE_AVATAR_WIDTH;
	int heightAvailable = height * (1 - HOR_LINE_INFO_PLAYER_HEIGHT);
	
	al_draw_scaled_bitmap(imageAvatar, 0, 0, originalWidth, originalHeight, 0, HOR_LINE_INFO_PLAYER_HEIGHT * height + 5, widthAvailable,
		heightAvailable, 0);
}

int main()
{
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	MainScreen screen;
	screen.drawScreen();

	return 0;
}
