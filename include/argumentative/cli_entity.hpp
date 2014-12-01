#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_HPP

#include <argumentative/cli_entity_metadata.hpp>
#include <string>

namespace argumentative
{
    struct cli_entity
    {
        cli_entity(cli_entity_metadata const* metadata = nullptr, std::string value = "")
            : _metadata(metadata)
            , _value(value)
        {}

        void invoke_handler() const
        {
            _metadata->invoke_handler(_value);
        }

        bool is_valid() const
        {
            return _metadata != nullptr;
        }

        void unset()
        {
            _metadata = nullptr;
        }

        cli_entity_metadata const* _metadata;
        std::string _value;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_HPP)