#define COMPANY_PRICE 500000

class Company
{
	private:
		char* nameCompany;
		int levelCMMI;
	public:
		Company(const char* name);
		~Company();

		char* getName();
		void setName(const char* name);

		void upLevel();
		void downLevel();
		int getLevel();

		int getCertificationCost();
};
