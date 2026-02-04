#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int		main()
{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	try
	{
		std::vector<int>::iterator it = easyfind(v, 20);
		std::cout << "vector found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "vector error: " << e.what() << std::endl;
	}

	std::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	try
	{
		std::list<int>::iterator it = easyfind(l, 999);
		std::cout << "list found: " << *it << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "list error: " << e.what() << std::endl;
	}

	return (0);
}