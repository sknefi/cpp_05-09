#include "Serializer.hpp"

int		main()
{
	Data	data;

	data._id = 1;
	data._name = static_cast<std::string>("Serial Serializator");

	uintptr_t	ptr = Serializer::serialize(&data);
	Data		*deserialized_data = Serializer::deserialize(ptr);
	
	if (&data == deserialized_data)
		std::cout << "OK" << std::endl;
	else
		std::cout << "NOT OK" << std::endl;

	return (0);
}