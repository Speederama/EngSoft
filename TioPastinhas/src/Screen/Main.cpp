# include "Main.hpp"


// Constructor
Main::Main(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT& event,
		Data& data) :
Screen(display, event), _data(data), _step(0) {

	// Fonts
	_load_font("main", config::misc::font::dejavu,
			25, {"white"});

}

// Destructor
Main::~Main(void) {
}

// Draws contents to display
const bool Main::draw(void) {

	if (_key.is_released(ALLEGRO_KEY_ESCAPE)) return true;

	_font["main"]->draw<Font::CENTER>(_palette, .5, .85,
			"MAIN SCREN!!! Wanna quit? press <ESC>");
	return false;

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
