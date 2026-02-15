#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

static const int kRobotomySignGrade = 72;
static const int kRobotomyExecGrade = 45;

RobotomyRequestForm::RobotomyRequestForm() :
	AForm("RobotomyRequestForm", kRobotomySignGrade, kRobotomyExecGrade),
	_target("default_target")
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
}

RobotomyRequestForm::RobotomyRequestForm( const std::string &target ) :
	AForm("RobotomyRequestForm", kRobotomySignGrade, kRobotomyExecGrade),
	_target(target)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
}

RobotomyRequestForm::RobotomyRequestForm( const RobotomyRequestForm &src ) :
	AForm(src),
	_target(src._target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm	&RobotomyRequestForm::operator=( const RobotomyRequestForm &src )
{
	if (this != &src)
	{
		AForm::operator=(src);
		// _target is const, cannot be reassigned
	}
	return (*this);
}

const std::string	&RobotomyRequestForm::getTarget() const
{
	return (_target);
}

void	RobotomyRequestForm::execute( const Bureaucrat &executor ) const
{
	if (!getIsSigned())
		throw FormNotSignedException();
	if (executor.getGrade() > getGradeToExec())
		throw GradeTooLowException();

	std::cout << "* Drilling noises *" << std::endl;
	if (std::rand() % 2)
		std::cout << _target << " has been robotomized successfully" << std::endl;
	else
		std::cout << "The robotomy of " << _target << " has failed" << std::endl;
}


