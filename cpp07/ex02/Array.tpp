#pragma once

template <typename T>
Array<T>::Array() :
	_arr(NULL),
	_size(0)
{
}

template <typename T>
Array<T>::Array( unsigned int n ) :
	_arr(n ? new T[n] : NULL),
	_size(n)
{
}

template <typename T>
Array<T>::Array( Array const &src ) :
	_arr(NULL),
	_size(0)
{
	*this = src;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _arr;
}

template <typename T>
Array<T>	&Array<T>::operator=( Array<T> const &rhs )
{
	if (this == &rhs)
		return (*this);
	delete[] _arr;
	_arr = (rhs._size ? new T[rhs._size] : NULL);
	_size = rhs._size;
	for (unsigned int i = 0; i < rhs._size; i++)
		_arr[i] = rhs._arr[i];
	return (*this);
}

template <typename T>
unsigned int	Array<T>::size() const
{
	return (_size);
}

template <typename T>
T	&Array<T>::operator[]( unsigned int i )
{
	if (i >= _size)
		throw IndexOutOfBoundsException();
	return (_arr[i]);
}

template <typename T>
T const	&Array<T>::operator[]( unsigned int i ) const
{
	if (i >= _size)
		throw IndexOutOfBoundsException();
	return (_arr[i]);
}

template <typename T>
const char	*Array<T>::IndexOutOfBoundsException::what() const throw()
{
	return ("Index is out of bounds");
}