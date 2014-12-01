#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_ARGUMENT_METADATA_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_ARGUMENT_METADATA_HPP

#include <argumentative/cli_entity_metadata.hpp>
#include <argumentative/dsel/argument.hpp>
#include <functional>
#include <string>

namespace argumentative
{
    struct argument_metadata : cli_entity_metadata
    {
        typedef std::function<void (std::string const&)> invoker_type;

        template <typename ValueType>
        argument_metadata(dsel::argument_description<ValueType> const& spec)
            : arg_name(spec.name)
        {
            typedef typename dsel::argument_description<ValueType>::parser_type parser_type;

            typename dsel::argument_description<ValueType>::handler_type handler = spec.handler;
            invoker = [this, handler] (std::string const& value) {
                handler(parser_type::parse(value));
            };
        }

        void invoke_handler(std::string const& value) const
        {
            invoker(value);
        }

        std::string const& name() const
        {
            return arg_name;
        }

        std::string const arg_name;

    private:
        invoker_type invoker;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_ARGUMENT_METADATA_HPP)