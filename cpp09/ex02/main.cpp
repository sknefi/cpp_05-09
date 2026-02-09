#include "PmergeMe.hpp"
#include <string>
#include <iostream>

static std::string	merge_argv( int argc, char *argv[] )
{
	std::string	merged_str;

	for (int i = 1; i < argc; i++)
	{
		if (i > 1)
			merged_str += ' ';
		merged_str += argv[i];
	}
	return merged_str;
}

int		main( int argc, char *argv[] )
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./PmergeMe [numbers]" << std::endl;
        return 1;
    }

	try
	{
		PmergeMe p(merge_argv(argc, argv));
		p.sort();
		std::cout << "OK" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: "<< e.what() << std::endl;
		return 1;
	}
	return 0;
}