#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_METADATA_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_CLI_METADATA_HPP

#include <argumentative/dsel/argument.hpp>
#include <argumentative/dsel/option.hpp>
#include <argumentative/cli_entity_metadata/option_metadata.hpp>
#include <argumentative/cli_entity_metadata/argument_metadata.hpp>
#include <map>
#include <list>
#include <iterator>

namespace argumentative
{
    struct cli_metadata
    {
        template <typename ValueType>
        void add(dsel::argument_description<ValueType> const& spec)
        {
            _arguments.push_back(argument_metadata(spec));
        }

        template <typename ValueType>
        void add(dsel::option_description<ValueType> const& spec)
        {
            _option_store.push_back(option_metadata(spec));

            option_metadata & added_spec = _option_store.back();

            if (!spec.long_name.empty()) {
                _options[spec.long_name] = &added_spec;
            }

            if (!spec.short_name.empty()) {
                _options[spec.short_name] = &added_spec;
            }
        }

        option_metadata const* get_option(std::string const& name) const
        {
            auto i = _options.find(name);
            return i == _options.end() ? nullptr : i->second;
        }

        argument_metadata const* get_argument(unsigned int index) const
        {
            if (index >= _arguments.size()) {
                return nullptr;
            }

            auto i = _arguments.begin();
            std::advance(i, index);
            return &*i;
        }

    private:
        std::map<std::string, option_metadata *> _options;
        std::list<argument_metadata> _arguments;

        std::list<option_metadata> _option_store;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_CLI_METADATA_HPP)