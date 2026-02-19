#pragma once

#include <vector>
#include <deque>
#include <string>
#include <exception>
#include <utility>

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
	 * Generate the Ford-Johnson sequence
	 * @param k - the size of the container 
	 * @param seq - the sequence to generate
	 */
	void	_ford_johnson_sequence( size_t k, std::vector<size_t> &seq ) const;
	
	/**
	 * Ford-Johnson sort for container.
	 * Steps:
	 *  1. Pair up elements (min/max in each pair)
	 *  2. Split into smalls/bigs
	 *  3. Recursively sort bigs
	 *  4. Build insertion order (Jacobsthal-based)
	 *  5. Insert smalls into the sorted bigs (binary search for the position)
	 *  6. Insert remainder if odd count (binary search for the position)
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
	 * Insert the smalls into the bigs
	 * @param Container &bigs - reference to the bigs container
	 * @param std::vector<size_t> const &fj_seq - reference to the Ford-Johnson sequence
	 * @param Container const &smalls - reference to the smalls container
	 * @param Container const &bigs_snapshot - reference to the bigs container snapshot
	 */
	void	_insert_smalls_to_bigs( Container &bigs,
									std::vector<size_t> const &fj_seq,
									Container const &smalls,
									Container const &bigs_snapshot ) const;

	/**
	 * Insert the remainder into the bigs
	 * @param Container &bigs - reference to the bigs container
	 * @param int rem - the remainder
	 */
	void	_insert_rem_to_bigs( Container &bigs, int rem ) const;
	
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

	size_t			size() const;
	Container const	&get_data() const;

	class ValidationException : public std::exception
	{
	public:
		const char	*what() const throw();
	};
};

#include "PmergeMe.tpp"
