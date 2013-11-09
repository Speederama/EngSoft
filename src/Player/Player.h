#include <list>
#include <string>

#include "../Company/Company.h"

#define INITIAL_RESOURCES 2000000

class Player {

	private:
		std::string namePlayer;
		std::string methodologyPlayer;
		std::string fileAvatar;
		std::list<Company> listCompanies;
		int pointsPlayer, resourcesPlayer;

		void updatePoints();
	public:
		Player(const char* namePlayer, const char* methodologyPlayer, const char* fileAvatar);

		inline const char* getName() const { return namePlayer.data(); }

		inline const char* getMethodology() const { return methodologyPlayer.data(); }

		inline int getNumEmpresas() const { return listCompanies.size(); }

		inline int getPoints() const { return pointsPlayer; }

		inline int getResources() const { return resourcesPlayer; }
		void addResources(int resources);
		int removeResources(int resources, bool force);

		int buyCompany(const char* nameCompany);

		int certifyCompany(const char* nameCompany);

		inline const std::list<Company>& getCompanies() const { return listCompanies; }

		inline const char* getFileAvatar() const { return fileAvatar.data(); }
};
