#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_HPP

#include <argumentative/dsel/argument.hpp>
#include <argumentative/dsel/option.hpp>
#include <argumentative/cli_metadata.hpp>
#include <argumentative/options_range.hpp>
#include <string>

namespace argumentative
{
    struct cli
    {
        cli(std::string const& program_name)
            : _program_name(program_name)
        {}

        template <typename ValueType>
        cli & operator += (dsel::argument_description<ValueType> const& spec)
        {
            _metadata.add(spec);
            return *this;
        }

        template <typename ValueType>
        cli & operator += (dsel::option_description<ValueType> const& spec)
        {
            _metadata.add(spec);
            return *this;
        }

        template <typename I>
        void parse(I start, I const& end) const
        {
            options_range<I> command_line(start + 1, end, _metadata);

            for (auto const& entity : command_line) {
                entity.invoke_handler();
            }
        }

    private:
        cli(cli const&);

        std::string _program_name;
        cli_metadata _metadata;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_HPP)