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

#include <iterator> // std::distance

void Span::addNumber( std::vector<int>::const_iterator begin,
                      std::vector<int>::const_iterator end )
{
    std::ptrdiff_t d = std::distance(begin, end);
    if (d < 0)
        throw TooManyNumbersInContainerException(); // or a different exception if you prefer

    size_t count = static_cast<size_t>(d);

    if (_v.size() + count > _n)
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

int		Span::shortestSpan() const
{
	if (_v.size() <= 1)
		throw NotEnoughItemsToCalcSpanException();
	
	std::vector<int>	tmp(_v);
	std::sort(tmp.begin(), tmp.end());

	int		best = std::numeric_limits<int>::max();
	for (size_t i = 1; i < tmp.size(); i++)
	{
		int	diff = tmp[i] - tmp[i - 1];
		if (diff < best)
			best = diff;
	}

	return (best);
}

int		Span::longestSpan() const
{
	if (_v.size() <= 1)
		throw NotEnoughItemsToCalcSpanException();
	
	std::vector<int>::const_iterator min = std::min_element(_v.begin(), _v.end());
	std::vector<int>::const_iterator max = std::max_element(_v.begin(), _v.end());

	return (*max - *min);
}

const char *Span::TooManyNumbersInContainerException::what() const throw()
{
	return ("Can't fit into container");
}

const char *Span::NotEnoughItemsToCalcSpanException::what() const throw()
{
	return ("Not enough items to calculate span");
}