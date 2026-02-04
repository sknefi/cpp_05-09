#pragma once

# include <iostream>
# include <algorithm>
# include <exception>


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
	void	addNumber( std::vector<int>::iterator const begin, std::vector<int>::iterator const end);

	void	shortestSpan() const;
	void	longestSpan()  const;

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