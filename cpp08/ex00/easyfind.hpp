#pragma once

# include <algorithm>
# include <exception>

class NotFoundException : public std::exception
{
public:
	virtual const char *what() const throw();
};

template <typename T>
typename T::iterator		easyfind( T &container, int x );

template <typename T>
typename T::const_iterator	easyfind( T const &container, int x );

#include "easyfind.tpp"