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
	us		-> micro seconds
*/

# define VECTOR "vector"
# define DEQUE "deque"

class PmergeMe
{
private:
	std::vector<int>	_vec; // 1st container
	std::deque<int>		_deq; // 2nd container
	
	
	/**
	 * Get current time in micro seconds
	 * @return current time in micro seconds
	 */
	double	_now_us();

	/**
	 * Display message from subject with time in micro seconds
	 * @param n - number of elements
	 * @param time_us - time in micro seconds
	 * @param c_name - container name
	 */
	void	_display_msg( size_t n, double time_us, std::string c_name );

	/**
	 * Display vector from subject with name
	 * @param v - vector to display
	 * @param name - name of the vector
	 */
	void	_display_vector( std::vector<int> const &v, std::string const &name );
	
	/**
	 * Parse the input string and fill both containers.
	 * Throws ValidationException if:
	 *  - token is not a number
	 *  - number <= 0
	 *  - number > INT_MAX
	 * @param input - input string
	 * @return void
	 */
	void	_parse_input( std::string const &input );
	
	/**
	 * Ford–Johnson sort for vector.
	 * Steps:
	 *  1. Pair up elements (min/max in each pair)
	 *  2. Split into smalls/bigs
	 *  3. Recursively sort bigs
	 *  4. Build insertion order (Jacobsthal-based)
	 *  5. Insert smalls into the sorted bigs
	 *  6. Insert remainder if odd count
	 * @param v - vector to sort
	 * @return void
	 */
	void	_ford_johnson_sort_vector( std::vector<int> &v );
	void	_ford_johnson_sort_deque( std::deque<int> &d );
	
	// --- Vector helpers ---
	void	_create_pairs_vector( std::vector<int> const &v, bool &has_rem, int &rem,
								  std::vector< std::pair<int, int> > &pairs );
	void	_extract_smalls_and_bigs( std::vector< std::pair<int,int> > const &p,
									  std::vector<int> &smalls,
									  std::vector<int> &bigs );
	void	_insert_smalls_to_bigs( std::vector<int> &bigs,
									std::vector<size_t> const &fj_seq,
									std::vector< std::pair<int, int> > const &pairs );
	void	_insert_rem_to_bigs( std::vector<int> &bigs, int const rem );

	// --- Deque helpers ---
	void	_create_pairs_deque( std::deque<int> const &d, bool &has_rem, int &rem,
								 std::deque< std::pair<int, int> > &pairs );
	void	_extract_smalls_and_bigs_deque( std::deque< std::pair<int,int> > const &p,
											std::deque<int> &smalls,
											std::deque<int> &bigs );
	void	_insert_smalls_to_bigs_deque( std::deque<int> &bigs,
										  std::vector<size_t> const &fj_seq,
										  std::deque< std::pair<int, int> > const &pairs );
	void	_insert_rem_to_bigs_deque( std::deque<int> &bigs, int const rem );

	// --- Shared ---
	void	_ford_johnson_sequence( size_t const k, std::vector<size_t> &seq );

public:
	PmergeMe();
	PmergeMe( std::string const &input );
	PmergeMe( PmergeMe const &other );
	~PmergeMe();

	PmergeMe &operator=( PmergeMe const &other );

	void	sort();
	void	set_input( std::string const &input );

	class ValidationException : public std::exception
	{
	public:
		const char	*what() const throw();
	};
};
