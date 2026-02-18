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

	double	_now_us() const;
	void	_parse_input( std::string const &input );
	void	_ford_johnson_sequence( size_t k, std::vector<size_t> &seq ) const;
	void	_ford_johnson_sort( Container &c );
	void	_create_pairs( Container const &c, bool &has_rem, int &rem,
							Container &smalls, Container &bigs ) const;
	void	_insert_smalls_to_bigs( Container &bigs,
									std::vector<size_t> const &fj_seq,
									Container const &smalls,
									Container const &bigs_snapshot ) const;
	void	_insert_rem_to_bigs( Container &bigs, int rem ) const;

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
