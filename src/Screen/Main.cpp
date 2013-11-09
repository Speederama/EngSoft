# include "Main.hpp"

# include <cmath>


// Constructor
Main::Main(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data), _angle(0.0), 
_time_to_stop(0), _time_rotating(0), _solve_roulette(false) {

	// Fonts
	_load_font("main", config::misc::font::dejavu, 25);
	_load_font("other", config::misc::font::dejavu,	20);
	_load_font("title", config::misc::font::dejavu, 30);

	_load_image("back", config::misc::image::main);
	_load_image("roulette", config::misc::image::roulette);
	_load_image("arrow", config::misc::image::arrow);
	_load_image("buy", config::misc::image::buy);
	_load_image("certification", config::misc::image::certification);

	_create_image("cover", .95 * _width, .9 * _height);
        _image["cover"]->set_color(_palette, "black", 200);

	_create_image("playerHor", .95 * _width, .3 * _height);
	_image["playerHor"]->set_color(_palette, "grey", 200);

	_create_image("playerVert", .35 * _height, .626 * _height);
	_image["playerVert"]->set_color(_palette, "grey", 200);

	_create_image("rounds", .95 * _width - .35 * _height + 1
		, .1 * _height);
	_image["rounds"]->set_color(_palette, "grey", 200);

	_create_image("lineHor", .4 * _width, .01 * _height);
	_image["lineHor"]->set_color(_palette, "white", 255);

	_create_image("lineVer", .01 * _height, .26 * _height);
	_image["lineVer"]->set_color(_palette, "white", 255);
}

// Destructor
Main::~Main(void) {
}

// Draws contents to display
void Main::draw(void) {

//	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;

	Image::set_target(_display);

	// Drawing grey panels...
	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);
	_image["cover"]->draw<Image::NORMAL>(.025, .05);
	_image["playerHor"]->draw<Image::NORMAL>(.025, .675);
	_image["playerVert"]->draw<Image::NORMAL>((_width - (.35 * _height)) 
		/ _width - .025, .05);
	_image["rounds"]->draw<Image::NORMAL>(.025, .05);

	// Drawing box for company info...
	_image["lineHor"]->draw<Image::NORMAL>(.49, .695);
	_image["lineHor"]->draw<Image::NORMAL>(.49, .945);
	_image["lineVer"]->draw<Image::NORMAL>(.49, .695);
	_image["lineVer"]->draw<Image::NORMAL>(.889, .695);

	// Drawing interactive elements
//	_image["roulette"]->draw<Image::NORMAL>(((.95 - (.35 * _height) 
//		/ _width) / 2 + 0.025) - (254.0 / _width), .07);
	_image["roulette"]->draw<Image::ROTATED>(((.95 - (.35 * _height) 
		/ _width) / 2 + 0.025), .4, 254, 232, _angle);
	_image["arrow"]->draw<Image::SCALED>(((.95 - (.35 * _height) 
		/ _width) / 2 + 0.025) - (25.0 / _width), .65 - (50.0
		/ _height), 50, 50);
	_image["buy"]->draw<Image::SCALED>(0.6, 0.2, 200, 130);
	_image["certification"]->draw<Image::SCALED>(0.6, 0.4, 200, 130);

	// Drawing current player related stuff...
	_data.player[_data.turn]->_avatar->draw<Image::SCALED>(.025, 
		.675, .15 * _width, .3 * _height);

	char namePlayer[100], procPlayer[100], recPlayer[100], 
		pointsPlayer[100]; 
	sprintf(namePlayer, "Nome: %s", _data.player[_data.turn]->_name.data());
	sprintf(procPlayer, "Process: %s", _data.player[_data.turn]->_process.data());
	sprintf(recPlayer, "Recursos: %d", _data.player[_data.turn]->_get_resources());
	sprintf(pointsPlayer, "Pontuação: %d", _data.player[_data.turn]->_get_points());
	_font["main"]->draw(_palette, "white", .2, .69, namePlayer);
	_font["main"]->draw(_palette, "white", .2, .77, procPlayer);
	_font["main"]->draw(_palette, "white", .2, .85, recPlayer);
	_font["main"]->draw(_palette, "white", .2, .93, pointsPlayer);

	for (int i(0); i < _data.player[_data.turn]->_num_companies(); ++i) {
		char compInfo[100];
		sprintf(compInfo, "Empresa %d - CMMI %d", i + 1, 
			_data.player[_data.turn]->_get_companies()[i]->_level());
		if (i < 3)
			_font["main"]->draw(_palette, "white", .5,
				.725 + 0.08 * i, compInfo);
		else
			_font["main"]->draw(_palette, "white", .7,
				.725 + 0.08 * (i - 3), compInfo);
	}

	// Drawing rounds info...
	char roundsInfo[100];
	sprintf(roundsInfo, "Rodada #%d de %d", _data.cur_round, _data.num_rounds);
	_font["title"]->draw(_palette, "white", .03, .075, roundsInfo);

	// Drawing info about other players...
	int count(0);
	for (int i(0); i < _data.player.size(); ++i) {
		if (i == _data.turn) continue;
		char info[100];
		sprintf(info, "%s - %d", _data.player[i]->_name.data(),
			 _data.player[i]->_get_points());
		_font["other"]->draw(_palette, "white", .8, 
			.1 * (count + 1), info);
		++count;
	}
	
	if (_time_rotating < _time_to_stop) {
		_angle += 3.1415 / (10 + exp((_time_rotating - 
			_time_to_stop / 2) * .1) * .01);
		if (_angle > 6.283) _angle -= 6.283;
		++_time_rotating;
	}
	else if (_time_rotating > 0) {
		_time_rotating = 0;
		_time_to_stop = 0;
	}
}

const bool Main::process() { 
	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;

	if (_data.cur_round > _data.num_rounds) return true;

	if (_time_rotating < _time_to_stop) return false;
	else if (_solve_roulette) _resolve_roulette();

	if (_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if(_event.mouse.x > .6 * _width and _event.mouse.x < 
			.6 * _width + 200 and _event.mouse.y > .2 * 
			_height + 30 and _event.mouse.y < .2 * _height 
			+ 97)	
			_buy_company();
		else if(_event.mouse.x > .6 * _width and _event.mouse.x < 
			.6 * _width + 200 and _event.mouse.y > .4 * 
			_height + 30 and _event.mouse.y < .4 * _height 
			+ 97)
			_certify_company();
		else {
			int centerX = ((.95 - (.35 * _height) / _width) 
				/ 2 + 0.025) * _width;
			int centerY = .4 * _height;
			int distSq = (_event.mouse.x - centerX) * 
				(_event.mouse.x - centerX) + 
				(_event.mouse.y - centerY) * 
				(_event.mouse.y - centerY);
			if (distSq <= 16900) {
				_time_to_stop = 200 + rand() % 100;
				_solve_roulette = true;
			}
		}
	}

	return false; 
}

void Main::_buy_company() {
	int answer = al_show_native_message_box(_display, "Comprar Empresa", 
		"Comprar Empresa", "Deseja realmente comprar uma nova empresa?", 
		"Sim|Não", ALLEGRO_MESSAGEBOX_YES_NO);
	bool success = true;
	if (answer == 1)
		success = _data.player[_data.turn]->_buy_company();
	if (not success)
		al_show_native_message_box(_display, "Comprar Empresa", "Erro!", "Não foi possível adquirir uma nova empresa. É possível que não existam recursos suficientes ou você já tenha atingido o limite de 6 empresas.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
}

void Main::_certify_company() {
	char options[200];
	bool first = true;
	for (int i(0); i < _data.player[_data.turn]->_num_companies(); ++i) {
		if (_data.player[_data.turn]->_get_companies()[i]->_level() < 5) {
			if (first)
				sprintf(options, "Empresa %d", i + 1);
			else
				sprintf(options, "%s|Empresa %d", options, i);
			first = false;
		}
	}
	
	if (first) {
		al_show_native_message_box(_display, "Certificar Empresa", 
			"Erro!", "Você não possui empresas a certificar!", 
			"OK", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	int answer = al_show_native_message_box(_display, "Certificar Empresa", 
		"Certificar Empresa", "Qual empresa deseja certificar?", 
		options, ALLEGRO_MESSAGEBOX_QUESTION);
	bool success = _data.player[_data.turn]->_certification(answer);
	if (not success)
		al_show_native_message_box(_display, "Certificar Empresa", "Erro!", "Não foi possível certificar a empresa. É possível que não existam recursos suficientes.", "OK", ALLEGRO_MESSAGEBOX_ERROR);
}

void Main::_resolve_roulette() {
	float piece = 6.283 / 12;
	int cur_piece = floor(_angle / piece);
	int answer = 0, chosen = 0, desired = 0;
	char full_text[1000];
	std::vector<Question*> questions_to_use;
	switch(cur_piece % 4) {
	case 0:
		if (_data.player[_data.turn]->_process == "XP")
			desired = 1;
		else if (_data.player[_data.turn]->_process == "Kanban")
			desired = 2;
		else if (_data.player[_data.turn]->_process == "Scrum")
			desired = 3;
		else if (_data.player[_data.turn]->_process == "Praxis")
			desired = 4;

		for (int i(0); i < _data.question.size(); ++i) {
			if (_data.question[i]->type == desired)
				questions_to_use.push_back(_data.question[i]);
		}

		chosen = rand() % questions_to_use.size();	
		sprintf(full_text, "%s\nA: %s\nB: %s\nc: %s\nD: %s",
			questions_to_use[chosen]->text.data(), 
			questions_to_use[chosen]->option[0].data(), 
			questions_to_use[chosen]->option[1].data(), 
			questions_to_use[chosen]->option[2].data(), 
			questions_to_use[chosen]->option[3].data());
		
		answer = al_show_native_message_box(_display, 
			"Pergunta Específica", "Pergunta Específica", 
			full_text, "A|B|C|D", 
			ALLEGRO_MESSAGEBOX_QUESTION);
		if (answer == 1) {
			al_show_native_message_box(_display,
				"Pergunta Específica",
				"Pergunta Específica",
				"Resposta correta!", "OK",
				ALLEGRO_MESSAGEBOX_OK_CANCEL);
			_data.player[_data.turn]->_add_resources(
				config::game::specific);
		}
		else {
			al_show_native_message_box(_display,
				"Pergunta Específica",
				"Pergunta Específica",
				"Resposta incorreta!", "OK",
				ALLEGRO_MESSAGEBOX_OK_CANCEL);
			_data.player[_data.turn]->_remove_resources(
				config::game::specific, true);
		}
		break;
	case 1:
		// TODO: bad luck event
		al_show_native_message_box(_display,
			"Evento de revés", "Evento de revés",
			"Evento de revés", "OK",
			ALLEGRO_MESSAGEBOX_OK_CANCEL);
		_data.player[_data.turn]->_remove_resources(
			500000, true);
		break;
	case 2:
		for (int i(0); i < _data.question.size(); ++i) {
			if (_data.question[i]->type == 0)
				questions_to_use.push_back(_data.question[i]);
		}

		chosen = rand() % questions_to_use.size();	
		sprintf(full_text, "%s\nA: %s\nB: %s\nc: %s\nD: %s",
			questions_to_use[chosen]->text.data(), 
			questions_to_use[chosen]->option[0].data(), 
			questions_to_use[chosen]->option[1].data(), 
			questions_to_use[chosen]->option[2].data(), 
			questions_to_use[chosen]->option[3].data());
		
		answer = al_show_native_message_box(_display, 
			"Pergunta Geral", "Pergunta Geral", 
			full_text, "A|B|C|D", 
			ALLEGRO_MESSAGEBOX_QUESTION);
		if (answer == questions_to_use[chosen]->correct) {
			al_show_native_message_box(_display,
				"Pergunta Geral",
				"Pergunta Geral",
				"Resposta correta!", "OK",
				ALLEGRO_MESSAGEBOX_OK_CANCEL);
			_data.player[_data.turn]->_add_resources(
				config::game::general);
		}
		else {
			al_show_native_message_box(_display,
				"Pergunta Geral",
				"Pergunta Geral",
				"Resposta incorreta!", "OK",
				ALLEGRO_MESSAGEBOX_OK_CANCEL);
			_data.player[_data.turn]->_remove_resources(
				config::game::general, true);
		}
		break;
	case 3:
		// TODO: good luck event
		al_show_native_message_box(_display,
			"Evento de sorte", "Evento de sorte",
			"Evento de sorte", "OK",
			ALLEGRO_MESSAGEBOX_OK_CANCEL);
		_data.player[_data.turn]->_add_resources(
			500000);
		break;
	}

	++_data.turn;
	if (_data.turn >= _data.player.size()) {
		_data.turn %= _data.player.size();
		++_data.cur_round;
	}
	_solve_roulette = false;
}

/*
for (int i(0); i < _player.size(); ++i) {

	list< pair<const char*, int> > info;
	for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
		info.push_back(pair<const char*, int>(it->getName(), it->getPoints()));

	list< pair<const char*, int> > copy;
	int count = 0;
	for (list< pair<const char*, int> >::iterator it = info.begin(); it != info.end(); ++it)
	{
		if (count != i)
			copy.push_back(*it);
		count++;
	}

	//TODO: Deal with outcome here...
	int outcome = 0;
	while (outcome < 1 || outcome > 10 )
	{
		list< pair<const char*, int> > companyInfo;
		if (players[i].getNumEmpresas() > 0)
		{
			for (list<Company>::const_iterator it = players[i].getCompanies().begin();
				it != players[i].getCompanies().end(); ++it)
				companyInfo.push_back(pair<const char*, int>(it->getName(), it->getLevel()));
		}

		screen.drawScreen(players[i].getFileAvatar(), currentRound, numberRounds, players[i].getName(),
			players[i].getMethodology(), players[i].getPoints(), players[i].getResources(), companyInfo, copy);
		outcome = screen.waitForEvent();

		//Outcome 1-4: General Question
		if (outcome >= 1 && outcome <= 4)
		{
			int correct = 1;
			if (outcome == correct)
			{
				players[i].addResources(100000);
				screen.showMessage("Pergunta Geral", "Pergunta Geral", "Resposta correta!", false);
			}
			else
			{
				players[i].removeResources(100000, true);
				screen.showMessage("Pergunta Geral", "Pergunta Geral", "Resposta incorreta!", true);
			}
		}
		//Outcome 5-8: Specific question
		else if (outcome >=5 && outcome <= 8)
		{
			int correct = 5;
			if (outcome == correct)
			{
				players[i].addResources(200000);
				screen.showMessage("Pergunta Específica", "Pergunta Específica", "Resposta correta!", false);
			}
			else
			{
				players[i].removeResources(200000, true);
				screen.showMessage("Pergunta Específica", "Pergunta Específica", "Resposta incorreta!", true);
			}
		}
		//Outcome 9: Lucky card
		else if (outcome == 9)
		{
			players[i].addResources(500000);
		}
		//Outcome 10: Bad luck card
		else if (outcome == 10)
		{
			players[i].removeResources(500000, true);
		}
		//Outcome 11: Company purchase
		else if (outcome == 11)
		{
			int num = players[i].getNumEmpresas();
			char name[1024];
			sprintf(name, "Empresa %d", num + 1);
			int out = players[i].buyCompany(name);
			if (out == -1)
				screen.showMessage("Compra de Empresa", "Compra de Empresa",
					"Você já possui uma empresa com esse nome", true);
			else if (out == 0)
				screen.showMessage("Compra de Empresa", "Compra de Empresa",
					"Você não possui recursos para comprar uma empresa", true);

		}
		//Outcome 12+: Certifications
		else if (outcome >= 12)
		{
			int index = outcome - 11;
			for (list<Company>::const_iterator it = players[i].getCompanies().begin();
				it != players[i].getCompanies().end(); ++it)
			{
				--index;
				if (index == 0)
				{
					int out = players[i].certifyCompany(it->getName());
					if (out == 0)
						screen.showMessage("Certificação de Empresa", "Certificação de Empresa",
							"Você não possui recursos para certificar essa empresa", true);
				}
			}
		}
	}
}
*/
