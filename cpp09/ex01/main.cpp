#include "RPN.hpp"

int		main( int argc, char *argv[] )
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./RPN [expression]" << std::endl;
		return 1;
	}

	try
	{
		RPN		rpn;
		rpn.process_expression(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}