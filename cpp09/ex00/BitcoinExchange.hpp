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
# include <cstdlib>

typedef std::string	Date;
typedef double		ExchangeRate;

# define DB_PATH 					"./data.csv"
# define CSV_VALID_COLOUMNS			"date,exchange_rate"
# define INPUT_FILE_HEADER			"date | value"
# define DEFAULT_INPUT_FILE_PATH	"./input.txt"

class BitcoinExchange
{
private:
	std::map<Date, ExchangeRate> _db;
	std::string					_input_file_path;

	/**
	 * Parse the database file and store the data in the _db map
	 * @param path - the path to the database file (also provided by the subject)
	 * @throws std::runtime_error - if the file is not a .csv file
	 * @throws std::runtime_error - if the file could not be opened
	 * @throws std::runtime_error - if the file has invalid coloumns
	 * @throws std::runtime_error - if the line is invalid
	 */
	void	_parse_db( std::string const &path );

	/**
	 * Process the input file, validate each line, lookup the closest exchange rate,
	 * and print the computed results/errors.
	 * @param path - the path to the input file (provided by the subject)
	 * @throws std::runtime_error - if the file could not be opened
	 * @throws std::runtime_error - if the file has invalid header
	 * @throws std::runtime_error - if the line is invalid
	 */
	void	_process_input_file( std::string const &path ) const;

public:
	BitcoinExchange();
	BitcoinExchange( std::string const &input_file_path );
	BitcoinExchange( BitcoinExchange const &src );
	~BitcoinExchange();

	BitcoinExchange &operator=( BitcoinExchange const &rhs );
	
	/**
	 * Set the input file path
	 * @param infile_path - the path to the input file
	 */
	void	set_input_file( std::string const &infile_path );

	/**
	 * Display the results of the input file
	 * @throws NoInputFileDefined - if the input file path is not set
	 */
	void	display_db() const;

	/**
	 * Exception thrown when the input file path is not set
	 * @return the error message
	*/
	class NoInputFileDefined : public std::exception
	{
	public:
		const char	*what() const throw();
	};
	
};
