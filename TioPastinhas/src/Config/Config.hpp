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
			const std::string config(path + "background.jpg");
		}

		namespace avatar {
			const int count = 1;
			const std::string path("../misc/avatar/");
			const std::string avatar[2] = {path, ".png"};
		}

		namespace sound {
			const std::string path("../misc/sounds/");
			const std::string intro(path + "silvio.wav");
		}

		namespace button {
			const std::string path("../misc/buttons/");
			const std::string add[2] = {path + "add", ".png"};
			const std::string cert[2] = {path + "certifica", ".png"};
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
