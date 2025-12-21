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
	if (literal.length() == 1 && !std::isdigit(literal[0])) {
		std::cout << std::fixed << std::setprecision(1); // float and double will have 1 decimal in print

		if (std::isprint(literal[0]))
			std::cout	<< "char: '"	<< literal[0] << "'" 				<< std::endl; 
		else
			std::cout	<< "char: Non displayable"							<< std::endl;
		std::cout		<< "int: "		<< static_cast<int>(literal[0])		<< std::endl;
		std::cout		<< "float: "	<< static_cast<float>(literal[0])	<< "f" << std::endl;
		std::cout		<< "double: "	<< static_cast<double>(literal[0])	<< std::endl;
		return ;
	}

	char	*end_ptr;
	double	d = std::strtod(literal.c_str(), &end_ptr);
	if (literal.c_str() == end_ptr) // end_ptr didn't move => no number found
	{
		std::cout << "Error: No number found" << std::endl;
		return ;
	}
	if (*end_ptr != '\0' && *end_ptr != 'f') // if found something else then 0 or f => garbage
	{
		std::cout << "Error: Invalid literal" << std::endl;
		return ;
	}

	// set how many digits after comma has to display
	if (d - static_cast<int>(d) == 0) // hasn't fractional part
		std::cout << std::fixed << std::setprecision(1);
	else 
		std::cout << std::setprecision(std::numeric_limits<double>::digits10);

	// char
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "char: impossible"						<< std::endl;
	else if (!std::isprint(static_cast<char>(d)))
		std::cout << "char: Non displayable"				<< std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d)		<< "'" << std::endl;
	
	// int
	if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
		std::cout << "int: impossible"						<< std::endl;
	else
		std::cout << "int: " << static_cast<int>(d)			<< std::endl;
	
	// float
	std::cout << "float: " << static_cast<float>(d) << "f"	<< std::endl;

	// double
	std::cout << "double: " << d							<< std::endl;
}
