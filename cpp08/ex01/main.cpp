#include "Span.hpp"
#include <vector>

void	print_vector( std::vector<int> const &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	
}

int		main()
{

	std::vector<int> z;
	z.push_back(11);

	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	print_vector(v);

	std::vector<int> u;
	u.push_back(1);
	u.push_back(2);
	u.insert(u.end(), v.begin(), v.end());

	print_vector(u);

	Span s(30);
	try
	{
		s.addNumber(1);
		s.addNumber(2);
		s.addNumber(3);
		// s.addNumber(4);
		s.addNumber(z.begin(), z.end());
		s.print_vector();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


	return (0);
}