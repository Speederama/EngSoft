# ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include "Error.hpp"


namespace config {

	// Information
	namespace data {

		const std::string title = "Roda o Software";

		namespace path {
			const std::string card = "../misc/data/events";
			const std::string question = "../misc/data/questions";
		}

	}

	// Game-related constants
	namespace game {

		const unsigned int max_players = 4;
		const unsigned int num_methods = 4;
		const char method[][7] =
			{"Praxis", "Kanban", "XP", "Scrum"};
		const unsigned int initial = 2000000;
		const unsigned int company = 500000;
		const unsigned int certification[4] = 
			{100000, 200000, 300000, 400000};
		const unsigned int points[5] = 
			{100, 200, 300, 400, 500};
		const unsigned int specific = 200000;
		const unsigned int general = 100000;

	}

	// Screen constants
	namespace screen {

		const int fps = 24;
		const int width = 1366;
		const int height = 768;

	}

	// Miscellaneous constants
	namespace misc {

		namespace font {
			const std::string dejavu("../misc/fonts/DejaVuSans.ttf");
		}

		namespace image {

			const std::string path("../misc/images/");
			const std::string splash(path + "splash2.png");
			const std::string config(path + "config.png");
			const std::string main(path + "background.png");
			const std::string roulette(path + "roleta.png");
			const std::string arrow(path + "seta.png");
			const std::string buy("../misc/buttons/compra.png");
			const std::string certification("../misc/buttons/certifica.png");
			const std::string podium(path + "cilindro.png");

		}

		namespace avatar {

			const int count = 4;
			const std::string path("../misc/images/");
			const std::string src("../misc/avatar/");
			const std::string bg(src + "info.png");
			const std::string silvio(path + "silvio.png");
			const std::string hebe(path + "hebe.png");
			const std::string xuxa(path + "xuxa.png");
			//const std::string gugu(path + "avatar.png");

		}

		namespace sound {
			const std::string path("../misc/sounds/");
			const std::string intro(path + "silvio.wav");
		}

		namespace button {

			const std::string path("../misc/buttons/");
			const std::string add(path + "add");
			const std::string tick(path + "tick");
			const std::string left(path + "left");
			const std::string right(path + "right");
			const std::string play(path + "jogar");
			const std::string menu(path + "menu");
			const std::string quit(path + "sair");

		}

	}

	// Errors
	namespace error {

		const Error load("Failed to load: ");
		const Error init("Failed to initialize Allegro5");
		const Error create("Failed to create: ");
		const Error display("Failed to create display");
		const Error invalid("Invalid option: ");

	}

}

# endif
