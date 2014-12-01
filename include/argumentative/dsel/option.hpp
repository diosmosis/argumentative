#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_OPTION_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_DSEL_OPTION_HPP

#include <argumentative/dsel/type.hpp>
#include <functional>
#include <string>

namespace argumentative { namespace dsel
{
    namespace option_value
    {
        enum type
        {
            none,
            optional,
            required
        };
    }

    template <typename ValueType>
    struct option_description
    {
        typedef ValueType value_type;
        typedef std::function<void (ValueType const&)> handler_type;
        typedef type<ValueType> parser_type;

        option_description(std::string const& long_name, std::string short_name, option_value::type value_spec)
            : long_name(long_name)
            , short_name(short_name)
            , value_spec(value_spec)
        {}

        option_description & operator [](handler_type const& h)
        {
            handler = h;
            return *this;
        }

        option_description & operator ()(handler_type const& h)
        {
            handler = h;
            return *this;
        }

        std::string long_name;
        std::string short_name;
        option_value::type value_spec;
        handler_type handler;
    };

    template <typename ValueType>
    inline option_description<ValueType> option(
        std::string const& long_name, std::string const& short_name, option_value::type value_spec, type<ValueType>)
    {
        return option_description<ValueType>(long_name, short_name, value_spec);
    }

    inline option_description<std::string> option(
        std::string long_name, std::string const& short_name = "", option_value::type value_spec = option_value::none)
    {
        return option_description<std::string>(long_name, short_name, value_spec);
    }
}}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_DSEL_OPTION_HPP)