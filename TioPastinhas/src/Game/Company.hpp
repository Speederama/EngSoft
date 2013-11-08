# ifndef COMPANY_HPP
# define COMPANY_HPP

struct Company {

public:
	// Constructor
	inline Company(void) :
	_levelCMMI(1) {}

	// Destructor
	~Company(void) {}

	inline const unsigned short _level(void) const { 
		return _levelCMMI; 
	}

	inline void _upgrade(void) {
		if (_levelCMMI < 5)
			++_levelCMMI;
	}

	inline void _downgrade(void) {
		if (_levelCMMI > 1)
			--_levelCMMI;
	}

private:
	unsigned short _levelCMMI;

};

# endif
