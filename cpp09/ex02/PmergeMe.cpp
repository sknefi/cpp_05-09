#include "PmergeMe.hpp"
#include <climits>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>


PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe( std::string const &input )
{
	_parse_input(input);
}

PmergeMe::PmergeMe( PmergeMe const &other )
{
	*this = other;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=( const PmergeMe &other )
{
	if (this != &other)
	{
		_vec = other._vec;
		_dec = other._dec;
	}
	return *this;
}

/**
 * Parse input to this->_vec, throw error if user input is not valid
 * "iss >> token" is splitting input by white characters, so it works like split()
 */
void	PmergeMe::_parse_input( std::string const &input )
{
	std::istringstream	iss(input);
	std::string			token;
	while (iss >> token) // this works as split, so
	{
		if (token.empty())
			continue;
		for (size_t i = 0; i < token.size(); ++i)
		{
			if (!std::isdigit(static_cast<unsigned char>(token[i])))
				throw ValidationException();
		}

		long	value = std::strtol(token.c_str(), 0, 10);
		if (value <= 0 || value > INT_MAX)
			throw ValidationException();
		_vec.push_back(static_cast<int>(value));
	}

	if (_vec.empty())
		throw ValidationException();
}


const char	*PmergeMe::ValidationException::what() const throw()
{
	return "VALIDATION - wrong input, usage: a positive integer sequence";
}