#include "PmergeMe.hpp"
#include <climits>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>
#include <algorithm>


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
			continue ;
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

#ifdef DEBUG
	static void		display_vec( std::vector<int> const &v, std::string const &name )
	{
		std::cout << name << ": ";
		for (size_t i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
	}
#endif

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
	#ifdef DEBUG
		display_vec(bigs, "bigs");
		display_vec(smalls, "smalls");
	#endif
}

std::vector<size_t>		PmergeMe::_ford_johnson_sequence(size_t k)
{
	std::vector<size_t>		seq;
	if (k == 0)
		return seq;

	// ---- 1) Build milestones (1-based): 1, 3, 5, 11, 21, ... up to k
	std::vector<size_t>		milestones;
	milestones.push_back(1);

	size_t j_prev = 0;
	size_t j_curr = 1;
	size_t last_added = 1;

	while (true)
	{
		size_t j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;

		if (j_curr > k)
			break;

		if (j_curr != last_added)
		{
			milestones.push_back(j_curr);
			last_added = j_curr;
		}
	}

	// ---- 2) Build order in 1-based indices using milestones
	std::vector<size_t>		order_1based;
	size_t					prev_m = 1;
	order_1based.reserve(k);
	order_1based.push_back(1);

	for (size_t mi = 1; mi < milestones.size(); ++mi)
	{
		size_t m = milestones[mi];
		// add m, m-1, ..., prev_m+1
		for (size_t x = m; x > prev_m; --x)
			order_1based.push_back(x);
		prev_m = m;
	}

	// ---- 3) Append the rest: k, k-1, ..., prev_m+1
	for (size_t x = k; x > prev_m; --x)
		order_1based.push_back(x);

	// ---- 4) Convert to 0-based
	seq.reserve(order_1based.size());
	for (size_t i = 0; i < order_1based.size(); ++i)
		seq.push_back(order_1based[i] - 1);

	return seq;
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

	std::vector<size_t>		fj_seq = _ford_johnson_sequence(bigs.size());


	for (size_t i = 0; i < fj_seq.size(); i++)
	{
		int		small = pairs[i].first;
		int		big = pairs[i].second;

		std::vector<int>::iterator	it_big = std::lower_bound(bigs.begin(), bigs.end(), big);
		std::vector<int>::iterator	it_small = std::lower_bound(bigs.begin(), it_big, small);

		bigs.insert(it_small, small);
	}
	
	if (has_rem)
	{
		std::vector<int>::iterator	it_rem = std::lower_bound(bigs.begin(), bigs.end(), rem);
		bigs.insert(it_rem, rem);
	}
	v = bigs;
	#ifdef DEBUG
		display_vec(v, "output");
	#endif
}

// void	PmergeMe::_ford_johnson_sort_deque( std::deque<int> &d )
// {

// }

/**
 * Ford-Jhonson sort
 */
void	PmergeMe::sort()
{
	#ifdef DEBUG
		display_vec(_vec, "input");
	#endif
	
	_ford_johnson_sort_vector(_vec);
	// _ford_johnson_sort_deque(_deq);
}

const char	*PmergeMe::ValidationException::what() const throw()
{
	return "VALIDATION - wrong input, usage: a positive integer sequence";
}