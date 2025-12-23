#include "whatever.hpp"
#include <iostream>

int		main()
{
	std::cout << "====== 42 TEST ======" << std::endl;
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	
	std::cout << "\n====== MY TEST ======" << std::endl;
	float g = 42.42f;
	float h = 21.21f;
	std::cout << "g = " << g << ", h = " << h << std::endl;
	::swap(g, h);
	std::cout << "g = " << g << ", h = " << h << std::endl;
	std::cout << "min( g, h ) = " << ::min(g, h) << std::endl;
	std::cout << "max( g, h ) = " << ::max(g, h) << std::endl;
	
	return (0);
}