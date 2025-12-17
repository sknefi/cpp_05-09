#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::Intern( const Intern &src )
{
	(void)src;
}

Intern::~Intern()
{
}

Intern &Intern::operator=( const Intern &src )
{
	(void)src;
	return (*this);
}

AForm *Intern::makeForm( const std::string &form_name, const std::string &target ) const
{
	const std::string	names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm *forms[3] = {
		new ShrubberyCreationForm(target),
		new RobotomyRequestForm(target),
		new PresidentialPardonForm(target)
	};

	for (int i = 0; i < 3; ++i)
	{
		if (form_name == names[i])
		{
			std::cout << "Intern creates " << form_name << std::endl;
			for (int j = 0; j < 3; ++j)	// delete other forms
			{
				if (j != i)
					delete forms[j];
			}
			return forms[i];
		}
	}

	std::cout << "Intern: unknown form name \"" << form_name << "\"" << std::endl;
	for (int j = 0; j < 3; ++j)
		delete forms[j];
	return 0;
}

