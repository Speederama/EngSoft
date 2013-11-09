# include <string>
# include <iostream>


class Error {

public:

	// Constructor -- all errors are fatal
	inline Error(const std::string& message) :
	_signal(EXIT_FAILURE), _message(message) {
	}

	// Functor
	inline void operator()(const std::string& value = "") const {

		std::cerr << _message;
		if (not value.empty()) std::cerr << '\'' << value << '\'';
		std::cerr << ';' << std::endl;
		std::exit(_signal);

	}

private:

	const int _signal;
	const std::string _message;

};
