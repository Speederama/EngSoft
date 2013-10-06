#include <string>

#define COMPANY_PRICE 500000

class Company
{
	private:
		std::string nameCompany;
		int levelCMMI;
	public:
		Company(const char* name);

		inline const char* getName() const { return nameCompany.data(); }

		void upLevel();
		void downLevel();
		inline int getLevel() const { return levelCMMI; }

		int getCertificationCost() const;
};
