#include "Bureaucrat.hpp"

int main()
{
	// Basic valid bureaucrat
	try
	{
		Bureaucrat a("Alica", 42);
		std::cout << a;

		a.increment();
		std::cout << "After increment: " << a.getName()
				  << " has grade " << a.getGrade() << std::endl;
		a.decrement();
		std::cout << "After decrement: " << a.getName()
		<< " has grade " << a.getGrade() << std::endl;

	}
	catch (const std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "-----------------------------" << std::endl;

	// Test too high grade on increment
	try
	{
		Bureaucrat high("High", MAX_GRADE);
		std::cout << high;

		std::cout << "Trying to increment " << high.getName() << std::endl;
		high.increment(); // should throw GradeTooHighException
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "-----------------------------" << std::endl;

	// Test too low grade on decrement
	try
	{
		Bureaucrat low("Low", MIN_GRADE);
		std::cout << low;

		std::cout << "Trying to decrement " << low.getName() << std::endl;
		low.decrement(); // should throw GradeTooLowException
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
