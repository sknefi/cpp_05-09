#include "ScalarConverter.hpp"

int		main(int argc, char *argv[])
{
	(void)argc;

	if (argc != 2)
	{
		std::cout << "Usage: <program_name> <scalar>" << std::endl;
		return 1;
	}

	std::cout <<argv[0]<< std::endl;
	ScalarConverter::convert(argv[1]);

	return (0);
}