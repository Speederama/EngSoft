#include <stdio.h>
#include <math.h>
#include <time.h>
#include <list>

#include "MainScreen.h"


using namespace std;

/* Initializes some variables.. */
MainScreen::MainScreen()
{
	display = NULL;
	imageRoullete = NULL;
	angle = 0.0;
	height = 0;
	width = 0;
}

/* Rotates the roullete that indicates action for turn */
int MainScreen::rotateRoullete()
{
	// Choose some random time to keep spinning...
	int t = 150 + rand() % 100;
	for (int i = 0; i < t; i++)
	{
		// Rotate it! The exponential part is only here to make it stop smoothly...
		angle += 3.1415 / (10 + exp((i - t / 2) * 0.1));
		if (angle > 6.283)
			angle -= 6.283;
		drawScreen();
	}

	// Check the results...
	float slice = 3.1415 / 6;
	int numSlices = (int) floor(angle / slice);
	switch (numSlices % 4)
	{
		case 0:
			return showQuestion(true) + 4;
		case 1:
			showCard(false);
			return 10;
		case 2:
			return showQuestion(false);
		case 3:
			showCard(true);
			return 9;
	}
	return 0;
}

/* Draws screen using current information */
int MainScreen::drawScreen()
{
	// If width/height has not been calculated yet...
	if (width == 0 || height == 0)
	{
		al_get_display_mode(0, &disp_data);
		width = (int) (0.9 * disp_data.width);
		height = (int) (0.85 * disp_data.height);
	}

	// If display has not been created yet...
	if (display == NULL)
	   	display = al_create_display(width, height);
	if(!display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(255, 255, 255));

	// Draw static stuff...
	drawBackground();
	drawLinesText();
	drawRoullete(angle);
	drawLegendArrow();
	drawButtons();

	// Draw player-related stuff..
	drawAvatar(fileImageAvatar.data());
	drawRounds(numRound, maxRounds);
	drawOtherPlayers(otherPlayers);
	drawPlayerInfo(namePlayer.data(), methodologyPlayer.data(), pointsPlayer, resourcePlayer, companiesPlayer);

	al_flip_display();

	return 1;
}

/* Draws screen reseting the current information */
int MainScreen::drawScreen(const char* fileImageAvatar, int numRound, int maxRounds, const char* namePlayer, const char* methodologyPlayer, 
	int pointsPlayer, int resourcesPlayer, const list< pair<const char*, int> >& companiesPlayer, 
	const list< pair<const char*, int> >& otherPlayers)
{
	// Grab new information...
	MainScreen::fileImageAvatar = fileImageAvatar;
	MainScreen::numRound = numRound;
	MainScreen::maxRounds = maxRounds;
	MainScreen::namePlayer = namePlayer;
	MainScreen::methodologyPlayer = methodologyPlayer;
	MainScreen::pointsPlayer = pointsPlayer;
	MainScreen::resourcePlayer = resourcesPlayer;
	MainScreen::companiesPlayer = companiesPlayer;
	MainScreen::otherPlayers = otherPlayers;
	
	// Check if width/height has not been calculated yet...
	if (width == 0 || height == 0)
	{
		//al_get_display_mode(0, &disp_data);
		//width = (int) (0.9 * disp_data.width);
		//height = (int) (0.85 * disp_data.height);
		width = (int) (0.9 * 1366);
		height = (int) (0.85 * 768);
	}

	// Check if display has not been created yet...
	if (display == NULL)
	   	display = al_create_display(width, height);
	if(!display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(255, 255, 255));

	// Draw static stuff...
	drawBackground();
	drawLinesText();
	drawRoullete(angle);
	drawLegendArrow();
	drawButtons();

	// Draw player-related stuff
	drawAvatar(fileImageAvatar);
	drawRounds(numRound, maxRounds);
	drawOtherPlayers(otherPlayers);
	drawPlayerInfo(namePlayer, methodologyPlayer, pointsPlayer, resourcesPlayer, companiesPlayer);

	al_flip_display();

	return 1;
}

/* Wait for action of the current player */
int MainScreen::waitForEvent()
{
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_EVENT event;
	al_register_event_source(queue, al_get_mouse_event_source());

	while (1)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			int centerX = VERT_LINE_PLAYERS_WIDTH * width / 2;
			int centerY = (HOR_LINE_INFO_PLAYER_HEIGHT - HOR_LINE_ROUNDS_HEIGHT) * height / 2;
			double dist = (event.mouse.x - centerX) * (event.mouse.x - centerX) + (event.mouse.y - centerY) * (event.mouse.y - centerY);
			if (dist <= 16900)
				return rotateRoullete();
			else if (event.mouse.y < 215 && event.mouse.y > 135 && event.mouse.x < VERT_LINE_PLAYERS_WIDTH * width && 
				event.mouse.x > VERT_LINE_PLAYERS_WIDTH * width - 200)
			{
				if (confirmPurchase() == 1)
					return 11;
				else
					return 0;
			}
			else if (event.mouse.y < 315 && event.mouse.y > 235 && event.mouse.x < VERT_LINE_PLAYERS_WIDTH * width && 
				event.mouse.x > VERT_LINE_PLAYERS_WIDTH * width - 200)
			{
				int answer = confirmCertification();
				if (answer == 0)
					return 0;
				else
					return 11 + answer;
			}
		}
	}

	return 0;
}

/* Shows message box to inform error to user */
void MainScreen::showMessage(const char* caption, const char* header, const char* text, bool error)
{
	if (error)
		al_show_native_message_box(display, caption, header, text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	else
		al_show_native_message_box(display, caption, header, text, "OK", ALLEGRO_MESSAGEBOX_OK_CANCEL);
}

/* Shows message box to confirm the purchase of a new company */
int MainScreen::confirmPurchase()
{
	int answer = al_show_native_message_box(display, "Compra de Empresa", "Compra de Empresa", 
		"Tem certeza que deseja investir R$ 500.000 na compra de uma empresa?", "Sim|Não", ALLEGRO_MESSAGEBOX_YES_NO);
	return answer;
}

/* Shows message box to allow user to select which company to improve */
int MainScreen::confirmCertification()
{
	if (companiesPlayer.size() > 0)
	{
		char text[1024];
		int count = 0;
		for (list< pair<const char*, int> >::iterator it = companiesPlayer.begin(); it != companiesPlayer.end(); ++it)
		{
			if (it->second < 5)
			{
				if (count == 0)
					sprintf(text, "%s (R$ %d)", it->first, it->second * 100000);
				else
					sprintf(text, "%s|%s (R$ %d)", text, it->first, it->second * 100000);
				count += 1;
			}
		}
		if (count > 0)
		{
			int answer = al_show_native_message_box(display, "Certificação de Empresa", "Certificação de Empresa", 
				"Qual empresa você deseja certificar?", text, ALLEGRO_MESSAGEBOX_QUESTION);
			return answer;
		}
		else
		{
			al_show_native_message_box(display, "Certificação de Empresa", "Certificação de Empresa", 
				"Todas suas empresas possuem o nível máximo de certificação!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return 0;
		}
	}
	else
	{
		al_show_native_message_box(display, "Certificação de Empresa", "Certificação de Empresa", 
			"Você não possui empresas para certificar", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
}

/* Shows message box with specific or general question */
int MainScreen::showQuestion(bool specific)
{
	int answer;
	if (specific)
		answer = al_show_native_message_box(display, "Pergunta Específica", "Pergunta Específica", 
			"Texto da pergunta", "A1|A2|A3|A4", ALLEGRO_MESSAGEBOX_QUESTION);
	else
		answer = al_show_native_message_box(display, "Pergunta Geral", "Pergunta Geral", "Texto da pergunta", 
			"A1|A2|A3|A4", ALLEGRO_MESSAGEBOX_QUESTION);
	return answer;
}

/* Shows message with good or bad luck card */
int MainScreen::showCard(bool lucky)
{
	int answer;
	if (lucky)
		answer = al_show_native_message_box(display, "Carta de Sorte", "Carta de Sorte", "Texto da carta", 
			"OK", ALLEGRO_MESSAGEBOX_OK_CANCEL);
	else
		answer = al_show_native_message_box(display, "Carta de Revés", "Carta de Revés", "Texto da carta", 
			"OK", ALLEGRO_MESSAGEBOX_OK_CANCEL);
	return answer;
}

/* Draws background image */
int MainScreen::drawBackground()
{
	ALLEGRO_BITMAP *imageBack = NULL;
	imageBack = al_load_bitmap("../misc/images/background.jpg");
	if (imageBack == NULL)
		return -1;

	al_draw_scaled_bitmap(imageBack, 0, 0, al_get_bitmap_width(imageBack), al_get_bitmap_height(imageBack), 0, 0, width, height, 0);
	al_destroy_bitmap(imageBack);
	return 1;
}

/* Draws some lines and text */
int MainScreen::drawLinesText()
{
	ALLEGRO_BITMAP *lineHorizontal = NULL;
	ALLEGRO_BITMAP *lineVertPlayers = NULL;
	ALLEGRO_BITMAP *lineVertAvatar = NULL;
	ALLEGRO_BITMAP *lineVertInventory = NULL;
	ALLEGRO_BITMAP *lineHorInventory = NULL;
	ALLEGRO_FONT *fontInvent = NULL;

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

	al_destroy_bitmap(lineHorizontal);
	al_destroy_bitmap(lineVertPlayers);
	al_destroy_bitmap(lineVertAvatar);
	al_destroy_bitmap(lineVertInventory);
	al_destroy_bitmap(lineHorInventory);

	fontInvent = al_load_ttf_font("../misc/fonts/DejaVuSans.ttf", 25, 0);
	if (fontInvent == NULL)
		return -1;

	al_draw_text(fontInvent, al_map_rgb(0, 0, 0), INVENTORY_TITLE_WIDTH * width, INVENTORY_TITLE_HEIGHT * height, 0, "Inventário");
	al_destroy_font(fontInvent);
	return 1;
}

/* Draws buttons for buying and improving companies */
int MainScreen::drawButtons()
{
	ALLEGRO_BITMAP *imageButtonBuy = NULL;
	imageButtonBuy = al_load_bitmap("../misc/images/botao_compra.png");
	if (imageButtonBuy == NULL)
		return -1;

	al_draw_scaled_bitmap(imageButtonBuy, 0, 0, al_get_bitmap_width(imageButtonBuy), al_get_bitmap_height(imageButtonBuy), 
		VERT_LINE_PLAYERS_WIDTH * width - 200, 100, 200, 150, 0);
	al_destroy_bitmap(imageButtonBuy);

	ALLEGRO_BITMAP *imageButtonCert = NULL;
	imageButtonCert = al_load_bitmap("../misc/images/botao_certifica.png");
	if (imageButtonCert == NULL)
		return -1;

	al_draw_scaled_bitmap(imageButtonCert, 0, 0, al_get_bitmap_width(imageButtonCert), al_get_bitmap_height(imageButtonCert), 
		VERT_LINE_PLAYERS_WIDTH * width - 200, 200, 200, 150, 0);
	al_destroy_bitmap(imageButtonCert);
	return 1;
}

/* Draws legend and arrow for roullete */
int MainScreen::drawLegendArrow()
{
	ALLEGRO_BITMAP *imageLegend = NULL;
	imageLegend = al_load_bitmap("../misc/images/legenda.png");
	if (imageLegend == NULL)
		return -1;

	al_draw_bitmap(imageLegend, 0, 0, 0);
	al_destroy_bitmap(imageLegend);

	ALLEGRO_BITMAP *imageArrow = NULL;
	imageArrow = al_load_bitmap("../misc/images/seta.png");
	if (imageArrow == NULL)
		return -1;

	al_draw_scaled_bitmap(imageArrow, 0, 0, al_get_bitmap_width(imageArrow), al_get_bitmap_height(imageArrow), 0.35 * width - 25, 
		0.55 * height, 50, 50, 0);
	al_destroy_bitmap(imageArrow);
	return 1;
}

/* Draws roullete rotated by some angle (in radians) */
int MainScreen::drawRoullete(float angle)
{
	if (imageRoullete == NULL)
		imageRoullete = al_load_bitmap("../misc/images/roleta.png");
	if (imageRoullete == NULL)
		return -1;

	al_draw_rotated_bitmap(imageRoullete, 254, 232, (VERT_LINE_PLAYERS_WIDTH / 2) * width,
		((HOR_LINE_INFO_PLAYER_HEIGHT - HOR_LINE_ROUNDS_HEIGHT) / 2 + HOR_LINE_ROUNDS_HEIGHT) * height, angle, 0);
	return 1;
}

/* Draws the info about rounds */
int MainScreen::drawRounds(int roundNumber, int totalRounds)
{
	ALLEGRO_FONT *fontRounds = NULL;
	fontRounds = al_load_ttf_font("../misc/fonts/DejaVuSans.ttf", 30, 0);
	if (fontRounds == NULL)
	{
		fprintf(stderr, "failed to load font file");
		return -1;
	}

	char rounds[1024];
	sprintf(rounds, "Rodada #%d de %d", roundNumber, totalRounds);
	al_draw_text(fontRounds, al_map_rgb(0, 0, 0), 0.005 * width, 0.005 * height, 0, rounds);
	al_destroy_font(fontRounds);
	return 1;
}

/* Draws info about other players */
int MainScreen::drawOtherPlayers(const list< pair<const char*, int> >& otherPlayers)
{
	ALLEGRO_FONT *fontOtherPlayers = NULL;
	fontOtherPlayers = al_load_ttf_font("../misc/fonts/DejaVuSans.ttf", 15, 0);
	if (fontOtherPlayers == NULL)
	{
		fprintf(stderr, "failed to load font file");
		return -1;
	}

	float offset = 0.0;
	for (list< pair<const char*, int> >::const_iterator it = otherPlayers.begin(); it != otherPlayers.end(); ++it)
	{
		char text[1024];
		sprintf(text, "%s - Pontuação: %d", it->first, it->second);
		al_draw_text(fontOtherPlayers, al_map_rgb(0, 0, 0), 0.76 * width, (0.1 + offset) * height, 0, text);
		offset += 0.1;
	}
	al_destroy_font(fontOtherPlayers);
	return 1;
}

int MainScreen::drawPlayerInfo(const char* playerName, const char* methodology, int currentPoints, int currentMoney, 
	const list< pair<const char*, int> >& companies)
{
	ALLEGRO_FONT *fontInfoPlayer = NULL;
	fontInfoPlayer = al_load_ttf_font("../misc/fonts/DejaVuSans.ttf", 15, 0);
	if (fontInfoPlayer == NULL)
	{
		fprintf(stderr, "failed to load font file");
		return -1;
	}

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
	sprintf(resource, "Recursos: R$ %d", currentMoney);
	al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), (VERT_LINE_AVATAR_WIDTH + 0.02) * width,
		(HOR_LINE_INFO_PLAYER_HEIGHT + 0.20) * height, 0, resource);

	int count = 0;
	for (list< pair<const char*, int> >::const_iterator it = companies.begin(); it != companies.end(); ++it)
	{
		char text[1024];
		sprintf(text, "%s - CMMI %d", it->first, it->second);
		if (count % 2 == 0)
			al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), 0.67 * width, (0.75 + 0.05 * (count / 2)) * height, 0, text);
		else
			al_draw_text(fontInfoPlayer, al_map_rgb(0, 0, 0), 0.81 * width, (0.75 + 0.05 * (count / 2)) * height, 0, text);
		count++;
	}

	al_destroy_font(fontInfoPlayer);
	return 1;
}

/* Draws avatar for current player */
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
	al_destroy_bitmap(imageAvatar);
	return 1;
}
