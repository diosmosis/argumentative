#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_ARGUMENT_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_DSEL_ARGUMENT_HPP

#include <argumentative/dsel/type.hpp>
#include <functional>
#include <string>

namespace argumentative { namespace dsel
{
    template <typename ValueType>
    struct argument_description
    {
        typedef ValueType value_type;
        typedef std::function<void (ValueType const&)> handler_type;
        typedef type<ValueType> parser_type;

        argument_description(std::string const& name)
            : name(name)
        {}

        argument_description & operator [](handler_type const& h)
        {
            handler = h;
            return *this;
        }

        argument_description & operator ()(handler_type const& h)
        {
            handler = h;
            return *this;
        }

        std::string name;
        handler_type handler;
    };

    template <typename ValueType>
    inline argument_description<ValueType> argument(std::string const& name, type<ValueType>)
    {
        return argument_description<ValueType>(name);
    }

    inline argument_description<std::string> argument(std::string const& name)
    {
        return argument_description<std::string>(name);
    }
}}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_ARGUMENT_HPP)