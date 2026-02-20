#pragma once

# include <iostream>
# include <string>
# include <stack>
# include <exception>

class RPN
{
	private:
		std::stack<double>	_s;

	public:
		RPN();
		RPN( RPN const &src );
		~RPN();

		RPN		&operator=( RPN const &src );

		void	process_expression( std::string const &exp );
};