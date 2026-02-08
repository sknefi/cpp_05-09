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

PmergeMe &PmergeMe::operator=( PmergeMe const &other )
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

void	PmergeMe::set_input( std::string const &input )
{
	_parse_input(input);
}

/**
 * Parse input to this->_vec, throw error if user input is not valid
 * "iss >> token" is splitting input by white characters, so it works like split()
 */
void	PmergeMe::_parse_input( std::string const &input )
{
	_vec.clear();
	_deq.clear();

	std::istringstream	iss(input);
	std::string			token;
	while (iss >> token)
	{
		#ifdef DEBUG
			std::cout << "Token: " << token << std::endl;
		#endif
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
		_deq.push_back(static_cast<int>(value));
	}

	if (_vec.empty() || _deq.empty())
		throw ValidationException();
}

void	PmergeMe::_ford_johnson_sort_vector( std::vector<int> &v )
{

}

void	PmergeMe::_ford_johnson_sort_deque( std::deque<int> &d )
{

}

/**
 * Ford-Jhonson sort
 */
void	PmergeMe::sort()
{
	_ford_johnson_sort_vector(_vec);
	_ford_johnson_sort_deque(_deq);
}

const char	*PmergeMe::ValidationException::what() const throw()
{
	return "VALIDATION - wrong input, usage: a positive integer sequence";
}