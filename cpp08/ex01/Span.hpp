#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <limits>


class Span
{
private:
	unsigned int		_n;
	std::vector<int>	_v;

public:
	Span();
	Span( unsigned int n );
	Span( Span const &src );
	~Span();

	Span &operator=( Span const &rhs );

	void	addNumber( int const x );
	void	addNumber( std::vector<int>::const_iterator begin,
					   std::vector<int>::const_iterator end );

	int		shortestSpan() const;
	int		longestSpan()  const;

	void	print_vector() const;

	class TooManyNumbersInContainerException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

	class NotEnoughItemsToCalcSpanException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

};