# ifndef PLAYER_HPP
# define PLAYER_HPP

#include "Company.hpp"
#include "../Allegro/Allegro.hpp"
#include "../Config/Config.hpp"

struct Player {

public:
	const std::string _name;
	const std::string _process;
	const Allegro::Image* _avatar;

	// Constructor
	Player(std::string name, std::string process, 
		Allegro::Image* avatar) :
	_name(name), _process(process), _avatar(avatar),
	_points(0), _resources(config::game::initial) {}

	// Destructor
	~Player(void) {
		for (int i(0); i < _companies.size(); ++i)
			delete _companies[i];
		_companies.clear();
		delete _avatar;
	}

	inline const unsigned int _num_companies() const {
		return _companies.size();
	}

	inline const unsigned int _get_points() const {
		return _points;
	}

	inline const unsigned int _get_resources() const {
		return _resources;
	}

	inline void _add_resources(unsigned int amount) {
		_resources += amount;
	}

	inline const bool _remove_resources(unsigned int amount, bool force) {
		if (amount > _resources and force) {
			_resources = 0;
			return true;
		}
		else if (amount > _resources) {
			return false;
		}
		else {
			_resources -= amount;
			return true;
		}
	}

	inline const bool _add_company() {
		if (_companies.size() >= 6) return false;
		Company* company = new Company();
		_companies.push_back(company);
		_update_points();
		return true;
	}

	inline const bool _remove_company(unsigned int number) {
		if (number >= _companies.size()) return false;
		std::vector<Company*>::iterator it = 
			_companies.begin(); 
		for (int i(0); i < number; ++i) ++it;
		_companies.erase(it);
		_update_points();
	}

	inline const bool _buy_company() {
		if (_companies.size() >= 6) return false;
		if (_remove_resources(config::game::company, false)) {
			Company* company = new Company();
			_companies.push_back(company);
			_update_points();
			return true;
		}
		else return false;
	}

	inline const bool _upgrade_company(unsigned int number) {
		if (number >= _companies.size()) return false;
		if (_companies[number]->_level() >= 5) return false;
		_companies[number]->_upgrade();
		_update_points();
		return true;
	}

	inline const bool _downgrade_company(unsigned int number) {
		if (number >= _companies.size()) return false;
		if (_companies[number]->_level() <= 1) return false;
		_companies[number]->_downgrade();
		_update_points();
		return true;
	}

	inline const bool _certification(unsigned int number) {
		if (number > _companies.size() + 1) return false;
		unsigned short cur_level = _companies[number - 1]->_level();
		if (cur_level == 5) return false;
		if (_remove_resources(config::game::certification[cur_level - 1], false)) {
			_companies[number - 1]->_upgrade();
			_update_points();
			return true;
		}
		else return false;
	}

	inline const std::vector<Company*>& _get_companies() const { return _companies; }

private:
	std::vector<Company*> _companies;
	unsigned int _points, _resources;

	inline void _update_points() {
		_points = 0;
		for (int i(0); i < _companies.size(); ++i)
			_points += config::game::points[_companies[i]->_level() - 1];
	}
};

# endif
