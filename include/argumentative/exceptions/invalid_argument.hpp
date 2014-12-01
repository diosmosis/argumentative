#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_ARGUMENT_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_ARGUMENT_HPP

#include <stdexcept>
#include <string>
#include <sstream>

namespace argumentative
{
    struct invalid_argument : std::runtime_error
    {
        invalid_argument(std::string word, unsigned int argument_index)
            : std::runtime_error(get_exception_message(word, argument_index))
        {}

        static std::string get_exception_message(std::string const& word, unsigned int argument_index)
        {
            std::stringstream ss;
            ss << "Unknown argument '" << word << "' encountered on command line at position " << argument_index << ".";
            return ss.str();
        }
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_EXCEPTIONS_INVALID_ARGUMENT_HPP)