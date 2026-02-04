#pragma once

# include <iostream>
# include <exception>
# include <cstddef>

template <typename T>
class Array
{
private:
	T				*_arr;
	unsigned int	_size;

public:
	Array();
	Array( unsigned int n );
	Array( Array const &src );
	~Array();

	Array	&operator=( Array const &rhs );
	
	unsigned int	size() const;
	T				&operator[]( unsigned int i );
	T const			&operator[]( unsigned int i ) const;
	
	class IndexOutOfBoundsException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};
};

#include "Array.tpp"