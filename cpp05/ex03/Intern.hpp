#ifndef INTERN_CPP
# define INTERN_CPP

# include <string>

class AForm;

class Intern
{
public:
	Intern();
	Intern( const Intern &src );
	~Intern();
	
	Intern &operator=( const Intern &src);

	AForm *makeForm( const std::string &form_name, const std::string &target ) const;
};

#endif // INTERN_CPP
