# ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include "Error.hpp"


namespace config {

	// Information
	namespace data {

		const std::string title = "Roda o Software";

		namespace path {
			const std::string card = "../misc/card.txt";
			const std::string question = "../misc/question.txt";
		}

	}

	// Game-related constants
	namespace game {
		const unsigned int initial = 2000000;
		const unsigned int company = 500000;
		const unsigned int certification[4] = 
			{100000, 200000, 300000, 400000};
		const unsigned int points[5] = 
			{100, 200, 300, 400, 500};
	}

	// Screen constants
	namespace screen {

		const int fps = 60;
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
			const std::string config(path + "background.png");
			const std::string roulette(path + "roleta.png");
			const std::string arrow(path + "seta.png");
			const std::string buy("../misc/buttons/compra.png");
			const std::string certification("../misc/buttons/certifica.png");
		}

		namespace avatar {
			const int count = 1;
			const std::string path("../misc/images/");
			const std::string avatar[2] = {path, ".png"};
			const std::string silvio(path + "avatar.jpg");
			const std::string hebe(path + "hebe.jpg");
			const std::string xuxa(path + "xuxa.jpg");
			//const std::string gugu(path + "avatar.png");
		}

		namespace sound {
			const std::string path("../misc/sounds/");
			const std::string intro(path + "silvio.wav");
		}

		namespace button {
			const std::string path("../misc/buttons/");
			const std::string add[2] = {path + "add", ".png"};
			const std::string cert[2] = {path + "certifica", ".png"};
			const std::string buy[2] = {path + "compra", ".png"};
			const std::string green[2] = {path + "verde", ".png"};
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
