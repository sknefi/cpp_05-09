#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public AForm {
private:
	const std::string	_target;

public:
	PresidentialPardonForm();
	PresidentialPardonForm( const std::string &target );
	PresidentialPardonForm( const PresidentialPardonForm &src );
	~PresidentialPardonForm();

	PresidentialPardonForm	&operator=( const PresidentialPardonForm &src );

	void				execute( const Bureaucrat &executor ) const;
	const std::string	&getTarget() const;
};

#endif


