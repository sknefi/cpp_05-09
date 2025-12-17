#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

static const int kPardonSignGrade = 25;
static const int kPardonExecGrade = 5;

PresidentialPardonForm::PresidentialPardonForm() :
	AForm("PresidentialPardonForm", kPardonSignGrade, kPardonExecGrade),
	_target("default_target")
{
}

PresidentialPardonForm::PresidentialPardonForm( const std::string &target ) :
	AForm("PresidentialPardonForm", kPardonSignGrade, kPardonExecGrade),
	_target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm( const PresidentialPardonForm &src ) :
	AForm(src),
	_target(src._target)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm	&PresidentialPardonForm::operator=( const PresidentialPardonForm &src )
{
	if (this != &src)
	{
		AForm::operator=(src);
		// _target is const, cannot be reassigned
	}
	return (*this);
}

const std::string	&PresidentialPardonForm::getTarget() const
{
	return (_target);
}

void	PresidentialPardonForm::execute( const Bureaucrat &executor ) const
{
	if (!get_is_signed())
		throw FormNotSignedException();
	if (executor.get_grade() > get_grade_to_exec())
		throw GradeTooLowException();

	std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}


