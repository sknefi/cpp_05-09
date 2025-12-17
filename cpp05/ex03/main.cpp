#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	try
	{
		std::cout << "=== ShrubberyCreationForm ===" << std::endl;
		Bureaucrat gardener("Gardener", 100);
		ShrubberyCreationForm shrub("home");

		std::cout << gardener;
		std::cout << shrub << std::endl;

		gardener.signForm(shrub);
		gardener.executeForm(shrub);

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== RobotomyRequestForm ===" << std::endl;
		Bureaucrat tech("Tech", 40);
		RobotomyRequestForm robo("Bender");

		std::cout << tech;
		tech.signForm(robo);
		tech.executeForm(robo);

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== PresidentialPardonForm ===" << std::endl;
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Ford Prefect");

		std::cout << president;
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception in main: " << e.what() << std::endl;
	}

	return (0);
}
