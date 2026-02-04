#include <iostream>
#include "Array.hpp"

static void	print_title(const std::string &s)
{
	std::cout << "\n=== " << s << " ===" << std::endl;
}

static void	print_int_array(const Array<int> &a)
{
	std::cout << "size=" << a.size() << " [ ";
	for (unsigned int i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "]" << std::endl;
}

int main()
{
	print_title("default construction + bounds");
	Array<int> a;
	std::cout << "a.size() = " << a.size() << std::endl;
	try
	{
		std::cout << a[0] << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "a[0] throws: " << e.what() << std::endl;
	}

	print_title("fill + read");
	Array<int> b(5);
	for (unsigned int i = 0; i < b.size(); ++i)
		b[i] = static_cast<int>(i) * 10;
	print_int_array(b);

	print_title("copy constructor (deep copy)");
	Array<int> c(b);
	b[0] = 999;
	std::cout << "after b[0]=999:" << std::endl;
	std::cout << "b: "; print_int_array(b);
	std::cout << "c: "; print_int_array(c);

	print_title("assignment operator (deep copy)");
	Array<int> d;
	d = b;
	b[1] = 777;
	std::cout << "after b[1]=777:" << std::endl;
	std::cout << "b: "; print_int_array(b);
	std::cout << "d: "; print_int_array(d);

	print_title("const access");
	const Array<int> e(c);
	std::cout << "e[2] = " << e[2] << std::endl;
	try
	{
		std::cout << e[999] << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cout << "e[999] throws: " << ex.what() << std::endl;
	}

	return (0);
}