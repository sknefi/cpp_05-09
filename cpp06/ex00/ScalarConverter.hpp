#pragma once

# include <iostream>
# include <string>
# include <limits>
# include <cmath>
# include <iomanip>

class ScalarConverter {
    private:
        ScalarConverter();
        ScalarConverter( ScalarConverter const &src ); 
        ScalarConverter &operator=( ScalarConverter const &rhs );
        ~ScalarConverter();

    public:
        static void		convert( std::string const &literal );
};
