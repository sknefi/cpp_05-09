#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

# define MAX_GRADE 1	// the best grade
# define MIN_GRADE 150	// the worst grade

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;

public:
	Bureaucrat();
	Bureaucrat( const std::string &name, const int grade );
	Bureaucrat( const Bureaucrat &src );
	~Bureaucrat();

	Bureaucrat		&operator =		( const Bureaucrat &src );

	const std::string	get_name() const;
	int					get_grade() const;

	void	increment();
	void	decrement();

	class GradeTooHighException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char *what() const throw();
	};

};

std::ostream	&operator <<	( std::ostream &stream, const Bureaucrat &b ); 

#endif