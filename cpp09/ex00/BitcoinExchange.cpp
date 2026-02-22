#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() :
	_input_file_path(DEFAULT_INPUT_FILE_PATH)
{
	_parse_db(DB_PATH);
}

BitcoinExchange::BitcoinExchange( std::string const &input_file_path ) :
	_input_file_path(input_file_path)
{
	_parse_db(DB_PATH);
}

BitcoinExchange::BitcoinExchange( BitcoinExchange const &src )
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange	&BitcoinExchange::operator=( BitcoinExchange const &rhs )
{
	if (this != &rhs)
	{
		_db = rhs._db;
		_input_file_path = rhs._input_file_path;
	}
	return *this;
}

void	BitcoinExchange::set_input_file( std::string const &infile_path )
{
	_input_file_path = infile_path;
}

/**
 * Trim the string: remove leading and trailing whitespace
 * @param s - the string to trim
 * @return the trimmed string
 */
static std::string	trim( std::string const &s )
{
    size_t	i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i])))
		i++;

    size_t	j = s.size();
    while (j > i && std::isspace(static_cast<unsigned char>(s[j - 1])))
		j--;

    return s.substr(i, j - i);
}

/**
 * Check if the year is a leap year
 * @param y - the year
 * @return true if the year is a leap year, false otherwise
 */
static bool		is_leap( int y )
{
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

/**
 * Get the number of days in the month
 * @param y - the year
 * @param m - the month
 * @return the number of days in the month
 */
static int		days_in_month( int y, int m )
{
    static const int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2)
		return d[1] + (is_leap(y) ? 1 : 0);
    return d[m - 1];
}

/**
 * Validate the date format: YYYY-MM-DD :
 * - Year: 4 digits
 * - Month: 2 digits (1-12)
 * - Day: 2 digits (1-31)
 * - The month must be between 1 and 12
 * - The day must be between 1 and 31
 * - The day must be valid for the month
 * - The year must be a leap year if the month is 2 and the day is 29
 * - The year must be a leap year if the year is divisible by 400
 * - The year must be a leap year if the year is divisible by 4 and not divisible by 100
 * @param date - the date to validate
 * @return true if the date is valid, false otherwise
 */
static bool		validate_date( const std::string &date )
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int y = std::atoi(date.substr(0,4).c_str());
    int m = std::atoi(date.substr(5,2).c_str());
    int d = std::atoi(date.substr(8,2).c_str());

    if (m < 1 || m > 12)
		return false;
    if (d < 1 || d > days_in_month(y, m))
		return false;

    return true;
}

/**
 * Validate the exchange rate
 * @param s - the exchange rate to validate
 * @param out - the exchange rate to validate
 * @return true if the exchange rate is valid, false otherwise
 */
static bool		validate_rate( std::string const &s, ExchangeRate &out )
{
    std::string		t = trim(s);
    if (t.empty())
		return false;

    char	*end = 0;
    out = std::strtod(t.c_str(), &end);

    while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
		end++;
	
	if (!end || !(*end == '\0'))
		return false;
	
	if (out < 0)
		return false;

    return true;
}

/**
 * Validate the value
 * @param s - the value to validate
 * @param out - the value to validate
 * @return true if the value is valid, false otherwise
 */
static bool		validate_value( std::string const &s, double &out )
{
	std::string		t = trim(s);
	if (t.empty())
		return false;

	size_t	i = 0;
	if (t[i] == '+' || t[i] == '-')
		++i;
	if (i >= t.size())
		return false;

	bool	has_digit = false;
	bool	has_dot = false;
	for (; i < t.size(); ++i)
	{
		char c = t[i];
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			has_digit = true;
			continue;
		}
		if (c == '.' && !has_dot)
		{
			has_dot = true;
			continue;
		}
		return false;
	}
	if (!has_digit)
		return false;

	char	*end = 0;
	out = std::strtod(t.c_str(), &end);

	while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
		end++;

	if (!end || *end != '\0')
		return false;

	return true;
}

/**
 * Format the double: remove trailing zeros and decimal point if it's 0
 * @param x - the double to format
 * @return the formatted string
 */
static std::string	format_double_clean( double x )
{
	std::ostringstream	oss;
	oss.setf(std::ios::fixed);
	oss << std::setprecision(10) << x;
	std::string		s = oss.str();

	std::string::size_type	dot = s.find('.');
	if (dot != std::string::npos)
	{
		while (!s.empty() && s[s.size() - 1] == '0')
			s.erase(s.size() - 1);
		if (!s.empty() && s[s.size() - 1] == '.')
			s.erase(s.size() - 1);
	}
	if (s.empty())
		return "0";
	return s;
}

/**
 * Find the exchange rate for the date, if the date is not found,
 * return the closest lower date
 * @param db - the database
 * @param date - the date to find the exchange rate for
 * @return the exchange rate for the date
 */
static std::map<Date, ExchangeRate>::const_iterator
	find_rate_for_date( std::map<Date, ExchangeRate> const &db, Date const &date )
{
	std::map<Date, ExchangeRate>::const_iterator it = db.lower_bound(date);
	if (it != db.end() && it->first == date)
		return it;
	if (it == db.begin())
		return db.end(); // no lower date exists
	if (it == db.end())
		return --it;
	return --it;
}

/**
 * Parse the database line
 * @param line - the line to parse
 * @param date - the date to parse
 * @param ex_rate - the exchange rate to parse
 * @throws std::runtime_error - if the line is invalid
 */
static void		parse_db_line( std::string const &line, Date &date, ExchangeRate &ex_rate )
{
	size_t	comma = line.find(',');
	if (comma == std::string::npos) // no comma
		throw std::runtime_error("Invalid line, missing columns - " + line);
	
	date = trim(line.substr(0, comma));
	std::string		ex_rate_str = trim(line.substr(comma + 1));
	if (!validate_date(date))
		throw std::runtime_error("Invalid line, WRONG format of date - " + line);
	
	if (!validate_rate(ex_rate_str, ex_rate))
		throw std::runtime_error("Invalid line, WRONG value of rate - " + line);
	

}

void	BitcoinExchange::_parse_db( std::string const &path )
{
	if (path.substr(path.size() - 4) != ".csv") // check if file is .csv
		throw std::runtime_error("File has to be in .csv format");
	
	std::ifstream	file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("DB (.csv file) could not be opened");
	
	std::string		columns;
	getline(file, columns);
	if (trim(columns) != CSV_VALID_COLOUMNS)
		throw std::runtime_error("DB (.csv file) has invalid columns");
	
	std::string		line;
	while (getline(file, line))
	{
		if (line.empty())
			continue ;

		Date			date;
		ExchangeRate	exchange_rate;

		#ifdef DEBUG
		std::cout << line << std::endl;
		#endif

		parse_db_line(line, date, exchange_rate);
		_db[date] = exchange_rate;
	}
	file.close();
}

/**
 * Parse the input line
 * @param line - the line to parse
 * @param date - the date to parse
 * @param value - the value to parse
 * @param value_str - the value string to parse
 * @return true if the line is valid, false otherwise
 */
static bool	parse_input_line(std::string const &line, Date &date, double &value, std::string &value_str)
{
	size_t	pipe = line.find('|');
	if (pipe == std::string::npos)
		return false;

	date = trim(line.substr(0, pipe));
	value_str = trim(line.substr(pipe + 1));

	if (!validate_date(date))
		return false;
	if (!validate_value(value_str, value))
		return false;
	return true;
}


/**
 * Get the bad input token,
 * example: "2011-01-33 | 3" => "2011-01-33"
 * @param line - the line to get the bad input token from
 * @return the bad input token
 */
static std::string	bad_input_token( std::string const &line )
{
	size_t pipe = line.find('|');
	if (pipe == std::string::npos)
		return trim(line);
	std::string		date_token = trim(line.substr(0, pipe));
	std::string		value_token = trim(line.substr(pipe + 1));
	double			dummy_value;

	if (!validate_date(date_token))
		return date_token;
	if (!validate_value(value_token, dummy_value))
		return value_token;
	return date_token;
}

void	BitcoinExchange::_process_input_file( std::string const &path ) const
{
	std::ifstream	file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file.");

	std::string	line;
	while (getline(file, line))
	{
		if (!trim(line).empty())
			break ;
	}
	if (file.eof() && trim(line).empty())
		throw std::runtime_error("could not open file.");
	if (trim(line) != INPUT_FILE_HEADER)
		throw std::runtime_error("input file has invalid columns definition => " + line);
	
	while (getline(file, line))
	{
		if (line.empty())
			continue ;

		Date	date;
		double	value;
		std::string value_str;
		if (!parse_input_line(line, date, value, value_str))
		{
			std::cout << "Error: bad input => " << bad_input_token(line) << std::endl;
			continue ;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue ;
		}

		std::map<Date, ExchangeRate>::const_iterator it = find_rate_for_date(_db, date);
		if (it == _db.end())
		{
			std::cout << "Error: bad input => " << bad_input_token(line) << std::endl;
			continue ;
		}

		double	result = value * it->second;
		std::cout << date << " => " << value_str << " = " << format_double_clean(result) << std::endl;
	}
	file.close();
}

void	BitcoinExchange::display_db() const
{
	if (_input_file_path.empty())
		throw NoInputFileDefined();
	_process_input_file(_input_file_path);
}

const char	*BitcoinExchange::NoInputFileDefined::what() const throw()
{
	return "could not open file.";
}
