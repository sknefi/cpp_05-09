#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() :
	_name("default"),
	_grade(100)
{
}

Bureaucrat::Bureaucrat( const std::string &name, const int grade ) :
	_name(name),
	_grade(grade)
{
	if (grade < MAX_GRADE)
		throw GradeTooHighException();
	if (grade > MIN_GRADE)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat( const Bureaucrat &src )
{
	*this = src;
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat &Bureaucrat::operator=( const Bureaucrat &src )
{
	if (this != &src)
	{
		// name is const
		_grade = src._grade;
	}
	return (*this);
}

const std::string	Bureaucrat::get_name() const 
{
	return (_name);
}

int					Bureaucrat::get_grade() const
{
	return (_grade);
}

void	Bureaucrat::increment()
{
	if (_grade <= MAX_GRADE)
		throw GradeTooHighException();
	_grade--;
}

void	Bureaucrat::decrement()
{
	if (_grade >= MIN_GRADE)
		throw GradeTooLowException();
	_grade++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat grade too high");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat grade too low");
}

std::ostream	&operator <<	( std::ostream &stream, const Bureaucrat &b )
{
	stream << b.get_name() << ", bureaucrat grade " << b.get_grade() << "." << std::endl;
	return (stream);
}

