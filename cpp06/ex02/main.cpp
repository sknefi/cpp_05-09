#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

Base	*generate()
{
	int random = std::rand() % 3;
	switch (random)
	{
	case 0:
		return (new A);
	case 1:
		return (new B);
	default:
		return (new C);
	}
}

void	identify( Base *p )
{
	if (dynamic_cast<A *>(p))
		std::cout << "it's A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "it's B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "it's C" << std::endl;
	else
		std::cout << "can't be identified, who did this" << std::endl;
}

void	identify( Base &p )
{
	try
	{
		A	&a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "it's A" << std::endl;
		return ;
	}
	catch(std::exception const &e) {}

	try
	{
		B	&b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << "it's B" << std::endl;
		return ;
	}
	catch(std::exception const &e) {}

	try
	{
		C	&c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << "it's C" << std::endl;
		return ;
	}
	catch(std::exception const &e) {}

	std::cout << "can't be identified, who did this" << std::endl;
}

int		main() {
	std::srand(std::time(0)); // seed the randomizer ONCE

	for (int i = 0; i < 5; i++) {
		std::cout << "Test " << i + 1 << ":" << std::endl;
		Base* ptr = generate();

		std::cout << "\tPointer: \t"; identify(ptr);
		std::cout << "\tReference: \t"; identify(*ptr);

		delete ptr;
		std::cout << "----------------" << std::endl;
	}
	return 0;
}