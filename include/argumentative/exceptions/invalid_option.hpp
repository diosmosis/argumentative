#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_OPTION_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_OPTION_HPP

#include <stdexcept>
#include <string>
#include <sstream>

namespace argumentative
{
    struct invalid_option : std::runtime_error
    {
        invalid_option(std::string word)
            : std::runtime_error(get_exception_message(word))
        {}

        static std::string get_exception_message(std::string const& word)
        {
            std::stringstream ss;
            ss << "Unknown option '" << word << "' encountered on command line.";
            return ss.str();
        }
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_OPTION_HPP)