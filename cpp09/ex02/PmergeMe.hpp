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
	rem		-> remainder
*/

class PmergeMe
{
private:
	std::vector<int>	_vec; // 1st container
	std::deque<int>		_deq; // 2nd container
	
	/**
	 * Parse the input string and fill both containers.
	 * Throws ValidationException if:
	 *  - token is not a number
	 *  - number <= 0
	 *  - number > INT_MAX
	 */
	void	_parse_input( std::string const &input );
	
	/**
	 * Ford–Johnson sort for vector.
	 * Steps:
	 *  1) Pair up elements (min/max in each pair)
	 *  2) Split into smalls/bigs
	 *  3) Recursively sort bigs
	 *  4) Build insertion order (Jacobsthal-based)
	 *  5) Insert smalls into the sorted bigs
	 *  6) Insert remainder if odd count
	 */
	void	_ford_johnson_sort_vector( std::vector<int> &v );
	
	/**
	 * Create pairs, where each pair.first < pair.second
	 * 
	 * @param v - vector to create pairs from
	 * @param has_rem - flag to check if there is odd number of numbers
	 * @param rem - remaining number
	 * @return vector of pairs
	 */
	std::vector< std::pair<int, int> >	
			_create_pairs_vector( std::vector<int> const &v, bool &has_rem, int &rem );
	
	/**
	 * Extract smalls and bigs from pairs: 
	 * 		in smalls store smaller number from pair
	 * 		in bigs store bigger number from pair
	 * 
	 * @param p - pairs to extract smalls and bigs from
	 * @param smalls - vector to store smaller numbers
	 * @param bigs - vector to store bigger numbers
	 * @return void
	 */
	void	_extract_smalls_and_bigs( std::vector< std::pair<int,int> > const &p,
									  std::vector<int> &smalls,
									  std::vector<int> &bigs );
	
	/**
	 * Create Ford Jhonson sequence, where each number is unique and in ascending order,
	 * it will help us reduce number of comparisons
	 * 
	 * @param k - number of pairs
	 * @return vector of indices
	 */
	std::vector<size_t>		_ford_johnson_sequence( size_t const k );

	/**
	 * Insert small number from pair to bigs, using Ford Jhonson sequence
	 * 
	 * @param bigs - vector to insert small numbers to
	 * @param fj_seq - Ford Jhonson sequence (indices to insert small numbers to)
	 * @param pairs - pairs to insert small numbers from
	 * @return void
	 */
	void					_insert_smalls_to_bigs( std::vector<int> &bigs,
													std::vector<size_t> const &fj_seq,
													std::vector< std::pair<int, int> > const &pairs );

	/**
	 * Insert remainder to bigs if odd number of numbers
	 * 
	 * @param bigs - vector to insert remainder to
	 * @param rem - remainder number
	 * @return void
	 */
	void					_insert_rem_to_bigs( std::vector<int> &bigs, int rem );

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