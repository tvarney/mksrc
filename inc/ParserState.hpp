
#ifndef MKSRC_PARSER_STATE_HPP
#define MKSRC_PARSER_STATE_HPP

#include <vector>
#include "Language.hpp"

namespace mksrc {
    struct ParserState {
        std::vector<Language> languages;
    };
    extern ParserState parser_state;
}

#endif
