#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() :
	_name("default_form"),
	_is_signed(false),
	_grade_to_sign(MIN_GRADE),
	_grade_to_exec(MIN_GRADE)
{
}

Form::Form( const std::string &name, int grade_to_sign, int grade_to_exec ) :
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

Form::Form( const Form &src ) :
	_name(src._name),
	_is_signed(src._is_signed),
	_grade_to_sign(src._grade_to_sign),
	_grade_to_exec(src._grade_to_exec)
{
}

Form::~Form()
{
}

Form &Form::operator=( const Form &src )
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

const std::string	Form::getName() const
{
	return (_name);
}

bool				Form::getIsSigned() const
{
	return (_is_signed);
}

int					Form::getGradeToSign() const
{
	return (_grade_to_sign);
}

int					Form::getGradeToExec() const
{
	return (_grade_to_exec);
}

void	Form::beSigned( const Bureaucrat &b )
{
	if (b.getGrade() > _grade_to_sign)
		throw GradeTooLowException();
	_is_signed = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat grade too high to sign the form");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat grade too low to sign the form");
}

std::ostream	&operator <<	( std::ostream &stream, const Form &f )
{
	stream	<< "Form " << f.getName() << " is " << (f.getIsSigned() ? "signed" : "not signed")
			<< ", grade to sign: " << f.getGradeToSign() << " and grade to execute: "
			<< f.getGradeToExec() << ".";
	return (stream);
}

