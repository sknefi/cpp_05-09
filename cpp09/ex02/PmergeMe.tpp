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
	std::cout << label << ": ";
	for (size_t i = 0; i < c.size(); ++i)
		std::cout << c[i] << " ";
	std::cout << std::endl;
}
#endif

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
		for (size_t i = 0; i < token.size(); ++i)
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
			std::cout << "parsed token: " << token << std::endl;
		#endif
	}

	if (_data.empty())
		throw ValidationException();

	#ifdef DEBUG
		debug_print_container(_data, "parsed input");
	#endif
}

template <typename Container>
void	PmergeMe<Container>::_ford_johnson_sequence( size_t k, std::vector<size_t> &seq ) const
{
	seq.clear();
	if (k == 0)
		return;
	seq.reserve(k);

	std::vector<size_t>	milestones;
	milestones.push_back(1);

	size_t	j_prev = 0;
	size_t	j_curr = 1;
	while (true)
	{
		size_t	j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
		if (j_curr > k)
			break;
		milestones.push_back(j_curr);
	}

	seq.push_back(0);
	size_t	prev_m = 1;
	for (size_t mi = 1; mi < milestones.size(); ++mi)
	{
		size_t m = milestones[mi];
		for (size_t x = m; x > prev_m; --x)
			seq.push_back(x - 1);
		prev_m = m;
	}
	for (size_t x = k; x > prev_m; --x)
		seq.push_back(x - 1);

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
void	PmergeMe<Container>::_insert_smalls_to_bigs( Container &bigs,
													 std::vector<size_t> const &fj_seq,
													 Container const &smalls,
													 Container const &bigs_snapshot ) const
{
	for (size_t i = 0; i < fj_seq.size(); ++i)
	{
		size_t	idx = fj_seq[i];
		int		small = smalls[idx];
		int		big = bigs_snapshot[idx];
		size_t	big_pos = _binary_search_pos(bigs, 0, bigs.size(), big);
		size_t	small_pos = _binary_search_pos(bigs, 0, big_pos, small);
		bigs.insert(bigs.begin() + small_pos, small);
	}
}

template <typename Container>
void	PmergeMe<Container>::_insert_rem_to_bigs( Container &bigs, int rem ) const
{
	size_t	rem_pos = _binary_search_pos(bigs, 0, bigs.size(), rem);
	bigs.insert(bigs.begin() + rem_pos, rem);
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
			if (c.size() <= 21)
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
		std::cout << "---- ford_johnson_sort size=" << c.size() << " ----" << std::endl;
		debug_print_container(c, "input");
	#endif

	bool		has_rem;
	int			rem;
	Container	smalls;
	Container	bigs;
	_create_pairs(c, has_rem, rem, smalls, bigs);

	#ifdef DEBUG
		debug_print_container(smalls, "smalls");
		debug_print_container(bigs, "bigs (pre-rec)");
		if (has_rem)
			std::cout << "remainder: " << rem << std::endl;
	#endif
	
	Container	bigs_snapshot = bigs;
	_ford_johnson_sort(bigs);

	#ifdef DEBUG
		debug_print_container(bigs, "bigs (sorted)");
	#endif

	std::vector<size_t>	fj_seq;
	_ford_johnson_sequence(smalls.size(), fj_seq);
	_insert_smalls_to_bigs(bigs, fj_seq, smalls, bigs_snapshot);

	#ifdef DEBUG
		debug_print_container(bigs, "after small insert");
	#endif

	if (has_rem)
		_insert_rem_to_bigs(bigs, rem);

	c.swap(bigs);
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
	for (size_t i = 0; i < _data.size(); ++i)
		std::cout << _data[i] << " ";
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
