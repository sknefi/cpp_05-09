#pragma once

# include <iostream>
# include <stdint.h>

struct Data
{
	int			_id;
	std::string	_name;
};

class Serializer
{
private:
	Serializer();
	Serializer( Serializer const &src );
	~Serializer();

	Serializer &operator=( Serializer const &rhs );

public:
	static uintptr_t	serialize ( Data *ptr );
	static Data			*deserialize( uintptr_t raw );

};
