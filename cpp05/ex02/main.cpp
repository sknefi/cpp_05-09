#include "Bureaucrat.hpp"
#include "AForm.hpp"

int main()
{
	try
	{
		std::cout << "=== Valid signing ===" << std::endl;
		Bureaucrat bob("Bob", 40);
		AForm      tax("Tax Form", 50, 25);

		std::cout << bob;
		std::cout << tax << std::endl;

		bob.signForm(tax);
		std::cout << tax << std::endl;

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== Too low grade to sign ===" << std::endl;
		Bureaucrat jim("Jim", 120);
		AForm      secret("Top Secret", 10, 5);

		std::cout << jim;
		std::cout << secret << std::endl;

		jim.signForm(secret);          // should fail and print why
		std::cout << secret << std::endl;

		std::cout << "-----------------------------" << std::endl;

		std::cout << "=== Already signed form ===" << std::endl;
		Bureaucrat alice("Alice", 30);
		AForm      contract("Contract", 50, 50);

		alice.signForm(contract);      // first time: signs
		alice.signForm(contract);      // second time: already signed
		std::cout << contract << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception in main: " << e.what() << std::endl;
	}

	return (0);
}
