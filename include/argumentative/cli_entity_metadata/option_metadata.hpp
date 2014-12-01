#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_OPTION_METADATA_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_OPTION_METADATA_HPP

#include <argumentative/cli_entity_metadata.hpp>
#include <argumentative/dsel/option.hpp>
#include <argumentative/dsel/type.hpp>
#include <functional>
#include <string>

namespace argumentative
{
    struct option_metadata : cli_entity_metadata
    {
        typedef std::function<void (std::string const&)> invoker_type;

        // TODO: lots of unnecessary copying here; should be able to just store the dsel::option<ValueType> instance
        //       same w/ argument_metadata
        template <typename ValueType>
        option_metadata(dsel::option_description<ValueType> const& spec)
            : long_name(spec.long_name)
            , short_name(spec.short_name)
            , value_spec(spec.value_spec)
        {
            typedef typename dsel::option_description<ValueType>::parser_type parser_type;

            typename dsel::option_description<ValueType>::handler_type handler = spec.handler;
            invoker = [this, handler] (std::string const& value) {
                handler(parser_type::parse(value));
            };
        }

        void invoke_handler(std::string const& value) const
        {
            invoker(value);
        }

        bool is_value_required() const // TODO: should handle option_value::none somewhere
        {
            return value_spec == dsel::option_value::required;
        }

        std::string const& name() const
        {
            return long_name;
        }

        std::string const long_name;
        std::string const short_name;
        dsel::option_value::type const value_spec;

    private:
        invoker_type invoker;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_OPTION_METADATA_HPP)