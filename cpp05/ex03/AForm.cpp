#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() :
	_name("default_form"),
	_is_signed(false),
	_grade_to_sign(MIN_GRADE),
	_grade_to_exec(MIN_GRADE)
{
}

AForm::AForm( const std::string &name, int grade_to_sign, int grade_to_exec ) :
	_name(name),
	_is_signed(false),
	_grade_to_sign(grade_to_sign),
	_grade_to_exec(grade_to_exec)
{
	if (grade_to_sign < MAX_GRADE || grade_to_exec < MAX_GRADE)
		throw GradeTooHighException();
	if (grade_to_sign > MIN_GRADE || grade_to_exec > MIN_GRADE)
		throw GradeTooLowException();
}

AForm::AForm( const AForm &src ) :
	_name(src._name),
	_is_signed(src._is_signed),
	_grade_to_sign(src._grade_to_sign),
	_grade_to_exec(src._grade_to_exec)
{
}

AForm::~AForm()
{
}

AForm &AForm::operator=( const AForm &src )
{
	if (this != &src)
	{
		// name is const
		// is_signed is const
		// grade_to_sign is const
		// grade_to_exec is const
		_is_signed = src._is_signed;
	}
	return (*this);
}

const std::string	AForm::getName() const
{
	return (_name);
}

bool				AForm::getIsSigned() const
{
	return (_is_signed);
}

int					AForm::getGradeToSign() const
{
	return (_grade_to_sign);
}

int					AForm::getGradeToExec() const
{
	return (_grade_to_exec);
}

void	AForm::beSigned( const Bureaucrat &b )
{
	if (b.getGrade() > _grade_to_sign)
		throw GradeTooLowException();
	_is_signed = true;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat grade too high to sign the form");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat grade too low to sign the form");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed");
}

std::ostream	&operator <<	( std::ostream &stream, const AForm &f )
{
	stream	<< "Form " << f.getName() << " is " << (f.getIsSigned() ? "signed" : "not signed")
			<< ", grade to sign: " << f.getGradeToSign() << " and grade to execute: "
			<< f.getGradeToExec() << ".";
	return (stream);
}

