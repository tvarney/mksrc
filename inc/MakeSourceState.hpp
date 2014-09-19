
#ifndef MKSRC_MAKE_SOURCE_STATE_HPP
#define MKSRC_MAKE_SOURCE_STATE_HPP

#include <string>
#include <vector>
#include "OutputLevel.hpp"
#include "ParserState.hpp"

namespace mksrc {
    class MakeSourceState {
    public:
        MakeSourceState();
        ~MakeSourceState() = default;
        
        bool parse(int argc, char **argv);
        bool parse(const char *filename);
        
        bool parse_languages(const std::string &directory);
        void report_languages() const;
    protected:
        const char *m_LicenseName;
        const char *m_DocstyleName;
        bool m_DoBody;
        OutputLevel::Value m_OutputLevel;
        ParserState m_Parser;
        
        std::vector<const char *> m_FileNames;
    };
}

#endif
