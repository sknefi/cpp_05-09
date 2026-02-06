#include "RPN.hpp"

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
	if (op == '/' && b == 0)
		throw std::runtime_error("Division by zero");
	
	switch (op)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
	throw std::runtime_error("Invalid operator");
}

// 8 9 * 9 - 9 - 9 - 4 - 1 +
void	RPN::process_expression( std::string const &exp )
{
	for (size_t i = 0; i < exp.size(); i++)
	{
		if (exp[i] == ' ')
			continue ;
		if (is_operand(exp[i]))
			_s.push(exp[i] - '0');
		else if (is_operator(exp[i]))
		{
			if (_s.size() < 2)
				throw std::runtime_error("Invalid expression");
			int		b = _s.top();
			_s.pop();
			int		a = _s.top();
			_s.pop();
			_s.push(apply_operator(a, b, exp[i]));
		}
		else
			throw std::runtime_error("Invalid character");
	}
	if (_s.size() != 1)
		throw std::runtime_error("Invalid expression");
	std::cout << _s.top() << std::endl;
}