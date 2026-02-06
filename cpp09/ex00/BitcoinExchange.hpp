#pragma once

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <exception>

typedef std::string	Date;
typedef double		ExchangeRate;

# define DB_PATH "./data.csv"
# define CSV_VALID_COLOUMNS "date,exchange_rate"

class BitcoinExchange
{
private:
	std::map<Date, std::string> _db;
	std::string					_input_file_path;

	// YYYY-MM-DD
	// float/int [0,1000]
	void	_parse_db( std::string const &path );
	bool	_validate_db( std::string date );
	void	_parse_input_file( std::string const &path );

	
public:
	BitcoinExchange();
	BitcoinExchange( std::string const &input_file_path );
	BitcoinExchange( BitcoinExchange const &src );
	~BitcoinExchange();

	BitcoinExchange &operator=( BitcoinExchange const &rhs );
	
	void	set_input_file( std::string const &infile_path );

	void	display_db() const;

	class NoInputFileDefined : public std::exception
	{
	public:
		const char	*what() const throw();
	};
	
};
