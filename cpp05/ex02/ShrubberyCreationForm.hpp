#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm {
private:
	const std::string	_target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm( const std::string &src );
	ShrubberyCreationForm( const ShrubberyCreationForm &src );
	~ShrubberyCreationForm();

	ShrubberyCreationForm	&operator = (const ShrubberyCreationForm &src);

	void				execute(const Bureaucrat &executor) const;
	const std::string	&getTarget() const;
};

#endif 