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

static void		parse_db_line( std::string const line, Date &date, ExchangeRate &ex_rate )
{
	size_t	comma = line.find(',');
	if (comma == std::string::npos) // no comma
		throw std::runtime_error("Invalid line, NO coloumns - " + line);
	
	date = trim(line.substr(0, comma));
	std::string	ex_rate_str = trim(line.substr(comma + 1));
	if (!validate_date(date))
		throw std::runtime_error("Invalid line, WRONG format of date - " + line);
	
	if (!validate_rate(ex_rate_str, ex_rate))
		throw std::runtime_error("Invalid line, WRONG value of rate - " + line);
	

}

void	BitcoinExchange::_parse_db( std::string const &path )
{
	std::ifstream	file(path);
	if (!file.is_open())
		throw std::runtime_error("DB (.csv file) could NOT be opened");
	
	std::string		coloumns;
	getline(file, coloumns);
	if (trim(coloumns) != "date,exchange_rate")
		throw std::runtime_error("DB (.csv file) has invalid coloumns");
	
	std::string		line;
	while (getline(file, line))
	{
		if (line.empty())
			continue;

		Date			date;
		ExchangeRate	exchange_rate;

		std::cout << line << std::endl;
		parse_db_line(line, date, exchange_rate);
		_db[date] = exchange_rate;
	}
	file.close();
}
