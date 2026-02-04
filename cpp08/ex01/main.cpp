#include <vector>
#include <cstdlib>	// rand, srand
#include <ctime>	// time
#include <iostream>

#include "Span.hpp"

static void	test_basic()
{
	std::cout << "\n=== BASIC TEST ===\n";
	Span sp(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	sp.print_vector();

	std::cout << "shortestSpan: " << sp.shortestSpan() << "\n"; // expected 2
	std::cout << "longestSpan : " << sp.longestSpan()  << "\n"; // expected 14
}

static void	test_not_enough()
{
	std::cout << "\n=== NOT ENOUGH ITEMS TEST ===\n";
	try
	{
		Span sp(10);
		sp.addNumber(42);
		std::cout << sp.shortestSpan() << "\n"; // should throw
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << "\n";
	}
}

static void	test_too_many()
{
	std::cout << "\n=== TOO MANY ITEMS TEST ===\n";
	try
	{
		Span sp(2);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3); // should throw
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught: " << e.what() << "\n";
	}
}

static void	test_range_insert()
{
	std::cout << "\n=== RANGE INSERT TEST ===\n";
	Span sp(6);

	std::vector<int> v;
	v.push_back(100);
	v.push_back(50);
	v.push_back(75);

	sp.addNumber(1);
	sp.addNumber(2);

	sp.addNumber(v.begin(), v.end()); // adds 100,50,75

	sp.print_vector();
	std::cout << "shortestSpan: " << sp.shortestSpan() << "\n";
	std::cout << "longestSpan : " << sp.longestSpan()  << "\n";

	// Now try overflowing with range
	try
	{
		std::vector<int> tooMuch;
		tooMuch.push_back(999);
		tooMuch.push_back(1000); // would exceed capacity (current size 5, cap 6)
		sp.addNumber(tooMuch.begin(), tooMuch.end()); // should throw
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught (range overflow): " << e.what() << "\n";
	}
}

static void	test_big()
{
	std::cout << "\n=== BIG TEST (10k) ===\n";
	Span sp(10000);

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 10000; ++i)
		sp.addNumber(std::rand());

	std::cout << "shortestSpan: " << sp.shortestSpan() << "\n";
	std::cout << "longestSpan : " << sp.longestSpan()  << "\n";
}

int		main()
{
	try
	{
		test_basic();
		test_not_enough();
		test_too_many();
		test_range_insert();
		test_big();
	}
	catch (const std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << "\n";
	}
	return 0;
}
