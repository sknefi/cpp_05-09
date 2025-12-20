#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter( ScalarConverter const &src )
{
	*this = src;
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter		&ScalarConverter::operator=( ScalarConverter const &rhs )
{
	(void) rhs;
	return *this;
}

void	ScalarConverter::convert( std::string const &literal )
{
	if (literal == "+inff" || literal == "+inf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return ;
	}
	
	if (literal == "-inff" || literal == "-inf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return ;
	}
	
	if (literal == "nanf" || literal == "nan")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return ;
	}
}