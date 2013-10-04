#include <list>
#include <string>

#include "Company.h"

#define INITIAL_RESOURCES 1000000

class Player
{
	private:
		std::string namePlayer;
		std::string methodologyPlayer;
		std::string fileAvatar;
		std::list<Company> listCompanies;
		int pointsPlayer, resourcesPlayer;

		void updatePoints();
	public:
		Player(const char* namePlayer, const char* methodologyPlayer, const char* fileAvatar);

		inline const char* getName() { return namePlayer.data(); }
		inline void setName(const char* name) { namePlayer = name; }

		inline const char* getMethodology() { return methodologyPlayer.data(); }
		inline void setMethodology(const char* name) { methodologyPlayer = name; }

		inline int getNumEmpresas() { return listCompanies.size(); }

		inline int getPoints() { return pointsPlayer; }

		inline int getResources() { return resourcesPlayer; }
		void addResources(int resources);
		void removeResources(int resources);

		int buyCompany(const char* nameCompany);

		int certifyCompany(const char* nameCompany);

		inline std::list<Company> getCompanies() { return listCompanies; }

		inline const char* getFileAvatar() { return fileAvatar.data(); }
};
