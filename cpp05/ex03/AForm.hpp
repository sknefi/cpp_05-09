#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat;

class AForm
{
private:
	const std::string	_name;
	bool				_is_signed;
	const int			_grade_to_sign;
	const int			_grade_to_exec;


public:
	AForm();
	AForm( const std::string &name, int grade_to_sign, int grade_to_exec );
	AForm( const AForm &src );
	virtual ~AForm();

	AForm		&operator =		( const AForm &src );

	const std::string	get_name() const;
	bool				get_is_signed() const;
	int					get_grade_to_sign() const;
	int					get_grade_to_exec() const;

	void				beSigned( const Bureaucrat &b );
	virtual void		execute( Bureaucrat const &executor ) const = 0;


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

	class FormNotSignedException : public std::exception
	{
	public:
		const char *what() const throw();
	};

};

std::ostream	&operator <<	( std::ostream &stream, const AForm &f ); 

#endif