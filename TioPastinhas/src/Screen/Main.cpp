# include "Main.hpp"


// Constructor
Main::Main(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data) {

	// Fonts
	_load_font("main", config::misc::font::dejavu, 25);

	_load_image("back", config::misc::image::config);
	_load_image("silvio", config::misc::avatar::silvio);
	_load_image("roulette", config::misc::image::roulette);
	_load_image("arrow", config::misc::image::arrow);

	_create_image("cover", .95 * _width, .9 * _height);
        _image["cover"]->set_color(_palette, "black", 200);

	_create_image("playerHor", .95 * _width, .3 * _height);
	_image["playerHor"]->set_color(_palette, "grey", 200);

	//_create_image("playerVert", .3 * _height, .9 * _height - (.3 * _height));
	_create_image("playerVert", .35 * _height, .626 * _height);
	_image["playerVert"]->set_color(_palette, "grey", 200);

	_load_button<Button::PUSH>("certification", config::misc::button::add, 0, 0, 80, 80);
}

// Destructor
Main::~Main(void) {
}

// Processes new events
const bool Main::process(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;
	return false;

}

// Draws contents to display
void Main::draw(void) {

	Image::set_target(_display);

	_font["main"]->draw<Font::CENTER>(_palette, "white",
			.5, .85,
			"MAIN SCREN!!! Wanna quit? press <ESC>");

	_image["back"]->draw<Image::SCALED>(0, 0, _width, _height);
	_image["cover"]->draw<Image::NORMAL>(.025, .05);
	_image["playerHor"]->draw<Image::NORMAL>(.025, .675);
	_image["playerVert"]->draw<Image::NORMAL>((_width - (.35 * _height)) 
		/ _width - .025, .05);
	_image["silvio"]->draw<Image::SCALED>(.025, .675, .15 * _width, 
		.3 * _height);
	_image["roulette"]->draw<Image::NORMAL>(((.95 - (.35 * _height) 
		/ _width) / 2 + 0.025) - (254.0 / _width), .07);
	_image["arrow"]->draw<Image::SCALED>(((.95 - (.35 * _height) 
		/ _width) / 2 + 0.025) - (25.0 / _width), .65 - (50.0
		/ _height), 50, 50);

	_button["certification"]->draw();

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
