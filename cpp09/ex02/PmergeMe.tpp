#include <climits>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <sys/time.h>
#include "PmergeMe.hpp"

template <typename Container>
PmergeMe<Container>::PmergeMe()
{
}

template <typename Container>
PmergeMe<Container>::PmergeMe( std::string const &input )
{
	_parse_input(input);
}

template <typename Container>
PmergeMe<Container>::PmergeMe( PmergeMe const &other )
{
	*this = other;
}

template <typename Container>
PmergeMe<Container>::~PmergeMe()
{
}

template <typename Container>
PmergeMe<Container>	&PmergeMe<Container>::operator=( PmergeMe const &other )
{
	if (this != &other)
		_data = other._data;
	return *this;
}

#ifdef DEBUG
template <typename Container>
static void		debug_print_container( Container const &c, std::string const &label )
{
	std::cerr << label << ": ";
	for (size_t i = 0; i < c.size(); i++)
		std::cerr << c[i] << " ";
	std::cerr << std::endl;
}
#endif

template <typename Container>
bool	PmergeMe<Container>::is_sorted()
{
	if (_data.size() == 1)
		return true;

	for (size_t i = 1; i < _data.size(); i++)
	{
		if (_data[i - 1] > _data[i])
			return false;
	}
	
	return true;
}

template <typename Container>
double	PmergeMe<Container>::_now_us() const
{
	timeval	tv;
	gettimeofday(&tv, 0);
	return (double)tv.tv_sec * 1000000.0 + (double)tv.tv_usec;
}

template <typename Container>
void	PmergeMe<Container>::_parse_input( std::string const &input )
{
	_data.clear();
	std::set<int>	seen;

	std::istringstream	iss(input);
	std::string			token;
	while (iss >> token)
	{
		for (size_t i = 0; i < token.size(); i++)
		{
			if (!std::isdigit(static_cast<unsigned char>(token[i])))
				throw ValidationException();
		}

		long value = std::strtol(token.c_str(), 0, 10);
		if (value <= 0 || value > INT_MAX)
			throw ValidationException();
		if (!seen.insert(static_cast<int>(value)).second)
			throw ValidationException();
		_data.push_back(static_cast<int>(value));
		#ifdef DEBUG
			std::cerr << "parsed token: " << token << std::endl;
		#endif
	}

	if (_data.empty())
		throw ValidationException();

	#ifdef DEBUG
		debug_print_container(_data, "parsed input");
	#endif
}

template <typename Container>
void	PmergeMe<Container>::_ford_johnson_sequence( size_t pend_count, std::vector<size_t> &seq ) const
{
	seq.clear();
	if (pend_count == 0)
		return ;
	seq.reserve(pend_count);

	// pend indices map to labels [b2, b3, ..., b(max_b)]
	size_t	max_b = pend_count + 1;
	size_t	prev_j = 1;

	size_t	j_prev = 0;
	size_t	j_curr = 1;
	while (true)
	{
		size_t	j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
		if (j_curr > max_b)
			break;
		for (size_t b = j_curr; b > prev_j; --b)
			seq.push_back(b - 2);
		prev_j = j_curr;
	}

	// Example with max_b = 11 (pend labels b2..b11):
	// Jacobsthal groups produce: b3,b2 then b5,b4 then b11,b10,b9,b8,b7,b6
	// Stored as 0-based pend indices: 1,0,3,2,9,8,7,6,5,4
	for (size_t b = max_b; b > prev_j; --b)
		seq.push_back(b - 2);

	#ifdef DEBUG
		debug_print_container(seq, "fj_seq");
	#endif
}

template <typename Container>
void	PmergeMe<Container>::_create_pairs( Container const &c, bool &has_rem, int &rem,
											Container &smalls, Container &bigs ) const
{
	smalls.clear();
	bigs.clear();

	size_t	i = 0;
	while (i + 1 < c.size())
	{
		int	lo = std::min(c[i], c[i + 1]);
		int	hi = std::max(c[i], c[i + 1]);
		smalls.push_back(lo);
		bigs.push_back(hi);
		i += 2;
	}
	has_rem = (i < c.size());
	rem = has_rem ? c[i] : -1;
}

template <typename Container>
void	PmergeMe<Container>::_insert_pend_to_chain( Container &chain,
													std::vector<size_t> const &fj_seq,
													Container const &smalls,
													std::vector<size_t> &big_pos,
													bool has_rem,
													int rem ) const
{
	size_t	small_pend_count = smalls.size() > 0 ? smalls.size() - 1 : 0;

	for (size_t i = 0; i < fj_seq.size(); i++)
	{
		size_t	pend_idx = fj_seq[i];
		bool	is_odd = has_rem && pend_idx == small_pend_count; // last element
		int		value = is_odd ? rem : smalls[pend_idx + 1];
		size_t	bound = is_odd ? chain.size() : big_pos[pend_idx + 1];
		size_t	pos = _binary_search_pos(chain, 0, bound, value);
		chain.insert(chain.begin() + pos, value);

		// increment every index after insertion
		for (size_t j = 0; j < big_pos.size(); j++)
		{
			if (big_pos[j] >= pos)
				big_pos[j]++;
		}
	}
}

template <typename Container>
size_t	PmergeMe<Container>::_binary_search_pos( Container const &c,
												 size_t left,
												 size_t right,
												 int value ) const
{
	while (left < right)
	{
		size_t	mid = left + (right - left) / 2;
		#ifdef DEBUG
			if (c.size() <= DEBUG_VAL)
			{
				std::cerr << "[cmp] c[" << mid << "]=" << c[mid]
						<< " < " << value << " ?  (range [" << left << ", " << right << "))\n";
			}
		#endif
		if (c[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

template <typename Container>
void	PmergeMe<Container>::_ford_johnson_sort( Container &c )
{
	if (c.size() <= 1)
		return;

	#ifdef DEBUG
		std::cerr << "---- ford_johnson_sort size=" << c.size() << " ----" << std::endl;
		debug_print_container(c, "input");
	#endif

	bool		has_rem;
	int			rem;
	Container	smalls;
	Container	bigs;
	_create_pairs(c, has_rem, rem, smalls, bigs);
	Container	orig_bigs = bigs; // orig_bigs[i] and smalls[i] is pair 

	#ifdef DEBUG
		debug_print_container(smalls, "smalls");
		debug_print_container(bigs, "bigs (pre-rec)");
		if (has_rem)
			std::cerr << "remainder: " << rem << std::endl;
	#endif
	
	_ford_johnson_sort(bigs);

	#ifdef DEBUG
		debug_print_container(bigs, "bigs (sorted)");
	#endif

	// Align smalls with recursively sorted bigs (preserve pair identity)
	// because of orig_bigs[i] and smalls[i] is pair 
	#ifdef DEBUG
		debug_print_container(orig_bigs, "===orig bigs");
	#endif
	Container	sorted_smalls;
	for (size_t i = 0; i < bigs.size(); i++)
	{
		size_t	orig_idx = 0;
		while (orig_idx < orig_bigs.size())
		{
			if (orig_bigs[orig_idx] == bigs[i])
				break;
			orig_idx++;
		}
		sorted_smalls.push_back(smalls[orig_idx]);
	}

	// Canonical main chain initialization: [b1, a1, a2, ...]
	Container	chain;
	chain.push_back(sorted_smalls[0]);
	for (size_t i = 0; i < bigs.size(); i++)
		chain.push_back(bigs[i]);

	// Current positions of partner a_i in main chain.
	std::vector<size_t>		big_pos(bigs.size());
	for (size_t i = 0; i < bigs.size(); i++)
		big_pos[i] = i + 1;

	size_t	pend_count = sorted_smalls.size() - 1 + (has_rem ? 1 : 0);
	std::vector<size_t>		fj_seq;
	_ford_johnson_sequence(pend_count, fj_seq);
	_insert_pend_to_chain(chain, fj_seq, sorted_smalls, big_pos, has_rem, rem);

	#ifdef DEBUG
		debug_print_container(chain, "after pend insert");
	#endif

	c.swap(chain);
}

template <typename Container>
void	PmergeMe<Container>::set_input( std::string const &input )
{
	_parse_input(input);
}

template <typename Container>
double	PmergeMe<Container>::sort()
{
	double	start = _now_us();
	_ford_johnson_sort(_data);
	return _now_us() - start;
}

template <typename Container>
void	PmergeMe<Container>::display( std::string const &label ) const
{
	std::cout << label << ": ";

	if (_data.size() < DEBUG_VAL)
	{
		for (size_t i = 0; i < _data.size(); i++)
			std::cout << _data[i] << " ";
	}
	else
		std::cout << "[...]";
	std::cout << std::endl;
}

template <typename Container>
size_t	PmergeMe<Container>::size() const
{
	return _data.size();
}

template <typename Container>
Container const	&PmergeMe<Container>::get_data() const
{
	return _data;
}

template <typename Container>
const char	*PmergeMe<Container>::ValidationException::what() const throw()
{
	return "VALIDATION - wrong input, usage: unique positive integer sequence";
}
