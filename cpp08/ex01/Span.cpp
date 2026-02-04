#include "Span.hpp"

Span::Span() :
	_n(0)
{
}

Span::Span( unsigned int n ) :
	_n(n)
{
}

Span::Span( Span const &src )
{
	*this = src;
}

Span::~Span()
{
}

Span	&Span::operator=( Span const &rhs )
{
	if (this != &rhs)
	{
		_n = rhs._n;
		_v = rhs._v;
	}
	return (*this);
}

void	Span::addNumber( int const x )
{
	if (_v.size() + 1 > _n)
		throw TooManyNumbersInContainerException();
	_v.push_back(x);
}

void	Span::addNumber( std::vector<int>::iterator const begin, std::vector<int>::iterator const end )
{
	if (_v.size() + std::distance(begin, end) > _n)
		throw TooManyNumbersInContainerException();
	_v.insert(_v.end(), begin, end);
}

void	Span::print_vector() const
{
	for (size_t i = 0; i < _v.size(); i++)
	{
		std::cout << _v[i] << " ";
	}
	std::cout << std::endl;
	
}

const char *Span::TooManyNumbersInContainerException::what() const throw()
{
	return ("Can't fit into container");
}

const char *Span::NotEnoughItemsToCalcSpanException::what() const throw()
{
	return ("Not enough items to calculate span");
}