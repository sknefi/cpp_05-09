#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <climits>

RPN::RPN()
{
}

RPN::RPN( RPN const &src )
{
	*this = src;
}

RPN::~RPN()
{
}

RPN	&RPN::operator=( RPN const &src )
{
	if (this != &src)
		_s = src._s;
	return (*this);
}

static inline bool	is_operator( char c )
{
	return c == '+' || c == '-' || c == '/' || c == '*';
}

static inline bool	is_operand( char c )
{
	return isdigit(c);
}

static int	apply_operator( int a, int b, char op )
{
	long long	res = 0;
	switch (op)
	{
		case '+': res = static_cast<long long>(a) + static_cast<long long>(b); break;
		case '-': res = static_cast<long long>(a) - static_cast<long long>(b); break;
		case '*': res = static_cast<long long>(a) * static_cast<long long>(b); break;
		case '/':
			if (op == '/' && b == 0)
				throw std::runtime_error("Division by zero");
			if (a == INT_MIN && b == -1)
				throw std::runtime_error("Integer overflow");
			return a / b;
		default:
			throw std::runtime_error("Invalid operator");
	}

	if (res < INT_MIN || res > INT_MAX)
		throw std::runtime_error("Integer overflow");
	
	return static_cast<int>(res);
}

// 8 9 * 9 - 9 - 9 - 4 - 1 +
void	RPN::process_expression( std::string const &exp )
{
	std::istringstream	iss(exp);
	std::string			token;

	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Invalid token");

		char	c = token[0];
		if (is_operand(c))
			_s.push(c - '0');
		else if (is_operator(c))
		{
			if (_s.size() < 2)
				throw std::runtime_error("Invalid expression");
			int		b = _s.top();
			_s.pop();
			int		a = _s.top();
			_s.pop();
			_s.push(apply_operator(a, b, c));
		}
		else
			throw std::runtime_error("Invalid character");
	}
	if (_s.size() != 1)
		throw std::runtime_error("Invalid expression");
	std::cout << _s.top() << std::endl;
}