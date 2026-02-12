#pragma once

#include <vector>
#include <deque>
#include <string>
#include <exception>

/**
	fj_		-> Ford Johnson
	j_		-> Jacobsthal
	m_		-> milestone
	it		-> iterator
*/

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
	
	void	_parse_input( std::string const &input );
	
	void	_ford_johnson_sort_vector( std::vector<int> &v );
	// void	_ford_johnson_sort_deque( std::deque<int> &d );
	
	//                     min, max
	std::vector< std::pair<int, int> >	
			_create_pairs_vector( std::vector<int> const &v, bool &has_rem, int &rem );
	
	void	_extract_smalls_and_bigs( std::vector< std::pair<int,int> > &p,
										std::vector<int> &smalls,
										std::vector<int> &bigs );
	
	std::vector<size_t>		_ford_johnson_sequence( size_t k );


public:
	PmergeMe();
	PmergeMe( std::string const &input );
	PmergeMe( PmergeMe const &other );
	~PmergeMe();

	PmergeMe &operator=( const PmergeMe &other );

	void	sort();
	void	set_input( std::string const &input );

	class ValidationException : public std::exception
	{
	public:
		const char	*what() const throw();
	};
};