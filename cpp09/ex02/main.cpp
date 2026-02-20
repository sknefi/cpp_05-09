#include "PmergeMe.hpp"
#include <string>
#include <iostream>
#include <iomanip>


static std::string	merge_argv( int argc, char *argv[] )
{
	std::string	merged_str;

	for (int i = 1; i < argc; i++)
	{
		if (i > 1)
			merged_str += ' '; // this is fine because I am "splitting" on whitespace
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
		std::string						input = merge_argv(argc, argv);
		PmergeMe< std::vector<int> >	vec_sorter(input);
		PmergeMe< std::deque<int> >		deq_sorter(input);

		vec_sorter.display("Before");
		double vec_time = vec_sorter.sort();
		double deq_time = deq_sorter.sort();
		vec_sorter.display("After");

		std::cout << "Time to process a range of "
				  << vec_sorter.size()
				  << " elements with std::"
				  << "vector"
				  << " : "
				  << std::fixed << std::setprecision(5)
				  << vec_time
				  << " us" << std::endl;
		std::cout << "Time to process a range of "
				  << deq_sorter.size()
				  << " elements with std::"
				  << "deque"
				  << " : "
				  << std::fixed << std::setprecision(5)
				  << deq_time
				  << " us" << std::endl;

		#ifdef DEBUG		
			std::cerr << ((vec_sorter.is_sorted() && deq_sorter.is_sorted()) ? "OK" : "WRONG") << std::endl;
		#endif
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: "<< e.what() << std::endl;
		return 1;
	}
	return 0;
}
