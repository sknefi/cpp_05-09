#pragma once

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <exception>

typedef std::string	Date;
typedef double		ExchangeRate;

# define DB_PATH 				"./data.csv"
# define CSV_VALID_COLOUMNS		"date,exchange_rate"
# define INPUT_FILE_HEADER		"date | value"

// BitcoinExchange loads a BTC exchange-rate database (CSV) into a sorted map.
// Then it reads an input file containing lines like:
//   YYYY-MM-DD | value
// and prints:
//   YYYY-MM-DD => value = value * closest_rate_at_or_before_date
class BitcoinExchange
{
private:
	// Key: date in format YYYY-MM-DD (lexicographically sortable).
	// Value: BTC exchange rate for that date.
	std::map<Date, ExchangeRate> _db;

	// Path to the user-provided input file (date | value).
	std::string					_input_file_path;

	// Parse the CSV database and fill _db.
	void	_parse_db( std::string const &path );
	// Parse the input file and print results/errors line by line.
	void	_parse_input_file( std::string const &path ) const;

	
public:
	BitcoinExchange();
	// Constructs the exchange and sets the input file path (DB is always loaded).
	BitcoinExchange( std::string const &input_file_path );
	BitcoinExchange( BitcoinExchange const &src );
	~BitcoinExchange();

	BitcoinExchange &operator=( BitcoinExchange const &rhs );
	
	// Set/replace the input file path.
	void	set_input_file( std::string const &infile_path );

	// Entry point: parses the input file and prints results.
	void	display_db() const;

	// Thrown when display_db() is called without setting an input file path.
	class NoInputFileDefined : public std::exception
	{
	public:
		const char	*what() const throw();
	};
	
};
