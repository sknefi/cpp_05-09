#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange()
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

static bool		is_leap( int y )
{
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static int		days_in_month( int y, int m )
{
    static const int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2)
		return d[1] + (is_leap(y) ? 1 : 0);
    return d[m - 1];
}

static bool		validate_date(const std::string& date)
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

static bool		validate_value( std::string const &s, double &out )
{
	std::string		t = trim(s);
	if (t.empty())
		return false;

	char	*end = 0;
	out = std::strtod(t.c_str(), &end);

	while (end && *end && std::isspace(static_cast<unsigned char>(*end)))
		end++;

	if (!end || *end != '\0')
		return false;

	return true;
}

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

static void		parse_db_line( std::string const &line, Date &date, ExchangeRate &ex_rate )
{
	size_t	comma = line.find(',');
	if (comma == std::string::npos) // no comma
		throw std::runtime_error("Invalid line, NO coloumns - " + line);
	
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
	
	std::ifstream	file(path);
	if (!file.is_open())
		throw std::runtime_error("DB (.csv file) could NOT be opened");
	
	std::string		coloumns;
	getline(file, coloumns);
	if (trim(coloumns) != CSV_VALID_COLOUMNS)
		throw std::runtime_error("DB (.csv file) has invalid coloumns");
	
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

// For "bad input" errors, the subject examples display only the date token.
// If the line contains '|', return the trimmed left side, otherwise the whole trimmed line.
static std::string	bad_input_token(std::string const &line)
{
	size_t pipe = line.find('|');
	if (pipe == std::string::npos)
		return trim(line);
	return trim(line.substr(0, pipe));
}

void	BitcoinExchange::_parse_input_file( std::string const &path ) const
{
	std::ifstream	file(path);
	if (!file.is_open())
		throw std::runtime_error("could not open file.");

	std::string		line;
	if (!getline(file, line))
		throw std::runtime_error("could not open file.");
	if (trim(line) != INPUT_FILE_HEADER)
		throw std::runtime_error("bad input => " + line);
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
	_parse_input_file(_input_file_path);
}

const char	*BitcoinExchange::NoInputFileDefined::what() const throw()
{
	return "could not open file.";
}
