#include "AForm.hpp"
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() :
	_name("default"),
	_grade(MIN_GRADE)
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

void	Bureaucrat::signForm( AForm &form )
{
	if (form.get_is_signed())
	{
		std::cout << _name << " cannot sign Form " << form.get_name() << " because it is already signed." << std::endl;
		return ;
	}
	try
	{
		form.beSigned(*this);
		std::cout << _name << " signed Form " << form.get_name() << "." << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << _name << " cannot sign Form " << form.get_name() << " because " << e.what() << std::endl;
	}
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

