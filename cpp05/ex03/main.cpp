#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

int main()
{
	try
	{
		Intern     someRandomIntern;
		Bureaucrat boss("Boss", 1);

		std::cout << "=== ShrubberyCreationForm via Intern ===" << std::endl;
		AForm *shrub = someRandomIntern.makeForm("shrubbery creation", "home");
		if (shrub)
		{
			std::cout << boss;
			std::cout << *shrub << std::endl;

			boss.signForm(*shrub);
			boss.executeForm(*shrub);
		}

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== RobotomyRequestForm via Intern ===" << std::endl;
		AForm *robo = someRandomIntern.makeForm("robotomy request", "Bender");
		if (robo)
		{
			std::cout << boss;
			std::cout << *robo << std::endl;

			boss.signForm(*robo);
			boss.executeForm(*robo);
		}

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== PresidentialPardonForm via Intern ===" << std::endl;
		AForm *pardon = someRandomIntern.makeForm("presidential pardon", "Ford Prefect");
		if (pardon)
		{
			std::cout << boss;
			std::cout << *pardon << std::endl;

			boss.signForm(*pardon);
			boss.executeForm(*pardon);
		}

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== Unknown form ===" << std::endl;
		AForm *unknown = someRandomIntern.makeForm("unknown form", "target");
		if (!unknown)
			std::cout << "Intern could not create unknown form" << std::endl;

		delete shrub;
		delete robo;
		delete pardon;
		delete unknown;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception in main: " << e.what() << std::endl;
	}

	return (0);
}