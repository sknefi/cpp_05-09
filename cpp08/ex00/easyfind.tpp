#pragma once

#include "easyfind.hpp"

inline const char *NotFoundException::what() const throw()
{
	return ("Not found");
}

template <typename T>
typename T::iterator	easyfind( T &container, int x )
{
	// treat typename T::iterator as data type
	typename T::iterator it = std::find(container.begin(), container.end(), x);
	if (it == container.end())
		throw NotFoundException();
	return it;
}

template <typename T>
typename T::const_iterator	easyfind( T const &container, int x )
{
	typename T::const_iterator it = std::find(container.begin(), container.end(), x);
	if (it == container.end())
		throw NotFoundException();
	return it;
}
