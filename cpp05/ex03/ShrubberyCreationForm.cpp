#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

static const int kShrubberySignGrade = 145;
static const int kShrubberyExecGrade = 137;

ShrubberyCreationForm::ShrubberyCreationForm() :
	AForm("ShrubberyCreationForm", kShrubberySignGrade, kShrubberyExecGrade),
	_target("default_target")
{
}

ShrubberyCreationForm::ShrubberyCreationForm( const std::string &target ) :
	AForm("ShrubberyCreationForm", kShrubberySignGrade, kShrubberyExecGrade),
	_target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm( const ShrubberyCreationForm &src ) :
	AForm(src),
	_target(src._target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=( const ShrubberyCreationForm &src )
{
	if (this != &src)
	{
		AForm::operator=(src);
		// _target is const, so we don't reassign it
	}
	return (*this);
}

const std::string	&ShrubberyCreationForm::getTarget() const
{
	return (_target);
}

void	ShrubberyCreationForm::execute( const Bureaucrat &executor ) const
{
	if (!get_is_signed())
		throw FormNotSignedException();
	if (executor.get_grade() > get_grade_to_exec())
		throw GradeTooLowException();

	std::ofstream ofs((_target + "_shrubbery").c_str());
	if (!ofs.is_open())
		return ;

	ofs << "       _-_" << std::endl;
	ofs << "    /~~   ~~\\" << std::endl;
	ofs << " /~~         ~~\\" << std::endl;
	ofs << "{               }" << std::endl;
	ofs << " \\  _-     -_  /" << std::endl;
	ofs << "   ~  \\\\ //  ~" << std::endl;
	ofs << "_- -   | | _- _" << std::endl;
	ofs << "  _ -  | |   -_" << std::endl;
	ofs << "      // \\\\" << std::endl;

	ofs.close();
}

