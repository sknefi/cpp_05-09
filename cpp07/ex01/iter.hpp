#pragma once

#include <iostream>
#include <cstddef>

template <typename T>
void	iter( T *array, size_t length, void (*f)(T &) )
{
	if (!array || !f)
		return ;
	for (size_t i = 0; i < length; i++)
		f(array[i]);
}

template <typename T>
void	iter( T const *array, size_t length, void (*f)(T const &) )
{
	if (!array || !f)
		return ;
	for (size_t i = 0; i < length; i++)
		f(array[i]);
}


template <typename F>
void	print( F const &value )
{
	std::cout << value << std::endl;
}