#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	bool				_is_signed;
	const int			_grade_to_sign;
	const int			_grade_to_exec;


public:
	Form();
	Form( const std::string &name, int grade_to_sign, int grade_to_exec );
	Form( const Form &src );
	~Form();

	Form		&operator =		( const Form &src );

	const std::string	get_name() const;
	bool				get_is_signed() const;
	int					get_grade_to_sign() const;
	int					get_grade_to_exec() const;
	void				beSigned( const Bureaucrat &b );

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

std::ostream	&operator <<	( std::ostream &stream, const Form &f ); 

#endif