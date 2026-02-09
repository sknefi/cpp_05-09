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

// 8 9 2 1 5 2 4 3
std::vector< std::pair<int, int> >
	PmergeMe::_create_pairs_vector( std::vector<int> const &v,
									bool &has_rem,
									int &rem )
{
	std::vector< std::pair<int, int> >	pairs;
	pairs.reserve(v.size() / 2);

	size_t	i = 0;
	while (i + 1 < v.size())
	{
		int		min = std::min(v[i], v[i + 1]);
		int		max = std::max(v[i], v[i + 1]);
		pairs.push_back(std::make_pair(min, max));
		i += 2;
	}
	has_rem	= i < v.size() ? true : false;
	rem		= i < v.size() ? v[i] : -1;
	return pairs;
}

void	PmergeMe::_extract_smalls_and_bigs( std::vector< std::pair<int,int> > &p,
											std::vector<int> &smalls,
											std::vector<int> &bigs )
{
	bigs.clear();
	smalls.clear();

	bigs.reserve(p.size());
	smalls.reserve(p.size());

	for (size_t i = 0; i < p.size(); i++)
	{
		smalls.push_back(p[i].first);
		bigs.push_back(p[i].second);
	}	
}
												

void	PmergeMe::_ford_johnson_sort_vector( std::vector<int> &v )
{
	if (v.size() <= 1)
		return ;

	bool	has_rem;
	int		rem;
	std::vector< std::pair<int, int> >	pairs;
	pairs = _create_pairs_vector(v, has_rem, rem);

	std::vector<int>	bigs;
	std::vector<int>	smalls;
	_extract_smalls_and_bigs(pairs, smalls, bigs);
	_ford_johnson_sort_vector(bigs);
	
	
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