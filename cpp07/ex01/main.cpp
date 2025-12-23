#include "iter.hpp"

int		main()
{
	std::cout << "\n====== INT TEST ======" << std::endl;
	int		tab[] = { 0, 1, 2, 3, 4 };
	iter(tab, 5, print);

	std::cout << "\n====== STRING TEST ======" << std::endl;
	std::string		strs[] = { "hello", "world", "this", "is", "a", "42" };
	iter(strs, 6, print);

	std::cout << "\n====== FLOAT TEST ======" << std::endl;
	float		floats[] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
	iter(floats, 5, print);

	std::cout << "\n====== DOUBLE TEST ======" << std::endl;
	double		doubles[] = { 0.1, 0.2, 0.3, 0.4, 0.5 };
	iter(doubles, 5, print);

	std::cout << "\n====== CHAR TEST ======" << std::endl;
	char		chars[] = { 'a', 'b', 'c', 'd', 'e' };
	iter(chars, 5, print);

	return (0);
}