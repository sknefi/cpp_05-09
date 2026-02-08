#pragma once

#include <vector>
#include <deque>
#include <exception>

class PmergeMe
{
    private:
        std::vector<int>					_vec;
        std::deque< std::pair<int, int> >	_dec;
		
		void	_parse_input( std::string const &input );


    public:
        PmergeMe();
		PmergeMe( std::string const &input );
        PmergeMe( PmergeMe const &other );
        ~PmergeMe();

        PmergeMe &operator=( const PmergeMe &other );

		void	sort();

		class ValidationException : public std::exception
		{
		public:
			const char	*what() const throw();
		};
};