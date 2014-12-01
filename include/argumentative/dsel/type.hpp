#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_TYPE_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_DSEL_TYPE_HPP

#include <string>
#include <sstream>
#include <stdexcept>

namespace argumentative
{
    template <typename T>
    struct type
    {
        static T parse(std::string const& value)
        {
            static std::stringstream ss;

            ss.clear();
            ss << value;

            T result;
            ss >> result;

            if (ss.fail()) {
                throw std::runtime_error(std::string("Invalid command line argument '") + value + "'.");
            }

            return result;
        }
    };

    template <>
    struct type<std::string>
    {
        static std::string const& parse(std::string const& value)
        {
            return value;
        }
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_TYPE_HPP)