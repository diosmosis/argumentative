#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_HPP

#include <string>

namespace argumentative
{
    struct cli_entity_metadata
    {
        virtual ~cli_entity_metadata() {}

        virtual void invoke_handler(std::string const& value) const = 0;

        virtual std::string const& name() const = 0;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_ENTITY_METADATA_HPP)