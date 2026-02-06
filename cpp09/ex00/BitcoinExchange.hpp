#pragma once

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <exception>
# include <cstdlib>
# include <cctype>
# include <sstream>
# include <iomanip>
# include <stdexcept>

typedef std::string	Date;
typedef double		ExchangeRate;

# define DB_PATH 				"./data.csv"
# define CSV_VALID_COLOUMNS		"date,exchange_rate"
# define INPUT_FILE_HEADER		"date | value"

class BitcoinExchange
{
private:
	std::map<Date, ExchangeRate> _db;
	std::string					_input_file_path;

	void	_parse_db( std::string const &path );
	void	_parse_input_file( std::string const &path ) const;

	
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
