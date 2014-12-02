#if !defined(ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_RANGE_HPP)
#define ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_RANGE_HPP

#include <argumentative/cli_entity.hpp>
#include <argumentative/cli_metadata.hpp>
#include <argumentative/cli_entity_metadata/option_metadata.hpp>
#include <argumentative/exceptions/invalid_option.hpp>
#include <argumentative/exceptions/invalid_argument.hpp>
#include <string>

namespace argumentative
{
    // TODO: make sure this conforms to standard container/iterator concepts
    template <typename I>
    struct options_range
    {
        typedef I word_iterator;
        typedef cli_entity const value_type;

        struct iterator
        {
            iterator(options_range const& super, word_iterator i, word_iterator end)
                : _super(super)
                , _i(i)
                , _end(end)
            {
                _i = _super.get_next_entity(_i, _current_entity);
            }

            cli_entity const& operator *() const
            {
                return _current_entity;
            }

            iterator const& operator ++()
            {
                _i = _super.get_next_entity(_i, _current_entity);
                return *this;
            }

            friend bool operator == (iterator const& lhs, iterator const& rhs)
            {
                return &lhs._super == &rhs._super && lhs._i == rhs._i
                    && lhs._current_entity.is_valid() == rhs._current_entity.is_valid();
            }

            friend bool operator != (iterator const& lhs, iterator const& rhs)
            {
                return !(lhs == rhs);
            }

        private:
            options_range const& _super;
            word_iterator _i;
            word_iterator _end;
            cli_entity _current_entity;
        };

        typedef iterator const_iterator;

        options_range(word_iterator start, word_iterator end, cli_metadata const& metadata)
            : _start(start)
            , _end(end)
            , _metadata(metadata)
            , argument_count(0)
        {}

        iterator begin() const { return iterator(*this, _start, _end); }
        iterator end() const { return iterator(*this, _end, _end); }

    private:
        friend struct iterator;

        word_iterator get_next_entity(word_iterator & i, cli_entity & entity) const
        {
            if (i == _end) {
                entity.unset();
                return _end;
            }

            cli_entity_metadata const* entity_metadata = nullptr;
            std::string value;

            // TODO: should use const string or something similar rather than creating new std::string instances
            std::string word(*i);

            // TODO: definitely ugly/inefficient code. need to fix.
            if (is_long_option(word)) {
                std::string option_str = strip_leading_dashes(word);

                value = get_embedded_option_value(option_str);

                option_metadata const* option_meta = _metadata.get_option(option_str);
                if (!option_meta) {
                    throw invalid_option(word);
                }

                if (option_meta->is_value_required()
                    && value.empty()
                ) {
                    value = get_next_word(i, _end);
                }

                entity_metadata = option_meta;
            } else if (is_short_option(word)) {
                std::string option_short_name = word.substr(1, 1);
                value = word.substr(2);

                option_metadata const* option_meta = _metadata.get_option(option_short_name);
                if (!option_meta) {
                    throw invalid_option(option_short_name);
                }

                if (option_meta->is_value_required()
                    && value.empty()
                ) {
                    value = get_next_word(i, _end);
                }

                entity_metadata = option_meta;
            } else {
                value = word;

                entity_metadata = _metadata.get_argument(argument_count);

                if (!entity_metadata) {
                    throw invalid_argument(word, argument_count);
                }

                ++argument_count;
            }

            entity = cli_entity(entity_metadata, value);

            ++i;

            return i;
        }

        bool is_short_option(std::string const& word) const
        {
            return word.size() > 2 && word[0] == '-' && word[1] != '-';
        }

        bool is_long_option(std::string const& word) const
        {
            return word.size() > 2 && word[0] == '-' && word[1] == '-';
        }

        std::string strip_leading_dashes(std::string const& word) const
        {
            size_t i = 0;
            while (i != word.size() && word[i] == '-') ++i;
            return word.substr(i);
        }

        std::string get_embedded_option_value(std::string & option_str) const
        {
            size_t equals_index = option_str.find('=');
            if (equals_index != std::string::npos) {
                std::string value = option_str.substr(equals_index + 1);

                option_str = option_str.substr(0, equals_index);

                return value;
            } else {
                return std::string();
            }
        }

        std::string get_next_word(word_iterator & i, word_iterator _end) const
        {
            ++i;

            if (i == _end) {
                return std::string();
            }

            return *i;
        }

        word_iterator _start;
        word_iterator _end;
        cli_metadata const& _metadata;
        mutable unsigned int argument_count;
    };
}

#endif // #if !defined(ARGUMENTATIVE_ARGUMENTATIVE_OPTIONS_RANGE_HPP)