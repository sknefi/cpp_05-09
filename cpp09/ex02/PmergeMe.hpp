#pragma once

# include <vector>
# include <deque>
# include <string>
# include <exception>
# include <utility>

# define DEBUG_VAL 21

/**
	fj_		-> Ford Johnson
	rem		-> remainder
	us		-> micro seconds
*/

template <typename Container>
class PmergeMe
{
private:
	Container	_data;

	/**
	 * Get the current time in microseconds
	 * @return the current time in microseconds
	 */
	double	_now_us() const;

	/**
	 * Parse the input and store the data in the container
	 * @param std::string const &input - the input to parse
	 * @throws ValidationException - if the input is invalid
	 */
	void	_parse_input( std::string const &input );

	/**
	 * Build pend insertion order (Jacobsthal groups then reverse tail).
	 * Order is returned as 0-based indices into pend (b2 starts at index 0).
	 * @param size_t pend_count - the number of pend elements
	 * @param std::vector<size_t> &seq - reference to the sequence of pend indices
	 */
	void	_ford_johnson_sequence( size_t pend_count, std::vector<size_t> &seq ) const;
	
	/**
	 * Ford-Johnson sort for container.
	 * Steps:
	 *  1. Pair up elements (small/big in each pair)
	 *  2. Recursively sort the big elements
	 *  3. Reorder small elements to keep pair identity with sorted bigs
	 *  4. Initialize main chain as [b1, a1, a2, ...]
	 *  5. Build pend insertion order (Jacobsthal groups, then reverse tail)
	 *  6. Insert pend elements with bounded binary search
	 * @param &c - reference to the container to sort
	 */
	void	_ford_johnson_sort( Container &c );

	/**
	 * Create pairs from the container
	 * @param const &c - reference to the container
	 * @param bool &has_rem - reference to the boolean to check if there is a remainder
	 * @param int &rem - reference to the remainder
	 * @param Container &smalls - reference to the smalls container
	 * @param Container &bigs - reference to the bigs container
	 */
	void	_create_pairs( Container const &c,
						   bool &has_rem,
						   int &rem,
						   Container &smalls,
						   Container &bigs ) const;
	
	
	/**
	 * Insert pend elements (b2.. and optional odd) into main chain.
	 */
	void	_insert_pend_to_chain( Container &chain,
								   std::vector<size_t> const &fj_seq,
								   Container const &smalls,
								   std::vector<size_t> &big_pos,
								   bool has_rem,
								   int rem ) const;
	
	/**
	 * Binary search for the position of the value in the container
	 * between the left and right indices using the binary search algorithm.
	 * @param Container const &c - reference to the container
	 * @param size_t left - the left index
	 * @param size_t right - the right index
	 * @param int value - the value to search for
	 * @return the position of the value in the container
	 */
	size_t	_binary_search_pos( Container const &c, size_t left, size_t right, int value ) const;

public:
	PmergeMe();
	explicit PmergeMe( std::string const &input );
	PmergeMe( PmergeMe const &other );
	~PmergeMe();

	PmergeMe	&operator=( PmergeMe const &other );

	void			set_input( std::string const &input );
	double			sort();
	void			display( std::string const &label ) const;
	bool			is_sorted();

	size_t			size() const;
	Container const	&get_data() const;

	class ValidationException : public std::exception
	{
	public:
		const char	*what() const throw();
	};
};

#include "PmergeMe.tpp"
