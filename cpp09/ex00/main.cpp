#include <iostream>

#include "BitcoinExchange.hpp"


int		main( int argc, char *argv[] )
{
	(void)argv;
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc [input_file]" << std::endl;
		return 1;
	}
	
	try
	{
		BitcoinExchange b(argv[1]);
		b.display_db();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
