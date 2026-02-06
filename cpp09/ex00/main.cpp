#include <iostream>

#include "BitcoinExchange.hpp"


int		main( int argc, char *argv[] )
{
	(void)argv;
	if (argc != 2)
	{
		std::cout << "Usage: ./btc [input_file]" << std::endl;
		return 1;
	}
	
	try
	{
		BitcoinExchange b;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return 0;
}
