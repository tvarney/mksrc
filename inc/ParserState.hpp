
#ifndef MKSRC_PARSER_STATE_HPP
#define MKSRC_PARSER_STATE_HPP

#include <string>
#include <vector>
#include "Language.hpp"
#include "language-parser.tab.hh"

#define YY_DECL                                         \
    yy::language_parser::token_type                     \
    yylex(yy::language_parser::semantic_type *yylval,   \
        yy::language_parser::location_type *yyloc,      \
          mksrc::ParserState &state)
YY_DECL;

namespace mksrc {
    class ParserState {
    public:
        ParserState();
        virtual ~ParserState();
        
        Language & current();
        Language & create();
        std::vector<Language> & languages();
        
        void scan_begin();
        void scan_end();
        
        int parse(const std::string &fname);
        
        void error(const yy::location &l, const std::string &message);
        void error(const std::string &message);
        
        std::string &file();
		
		int getSuffixIndex() const;
		void setSuffixIndex(int index);
    protected:
        std::string m_FileName;;
        
        bool m_TraceScanning, m_TraceParsing;
        std::vector<Language> m_Languages;
		int m_SuffixIndex;
    };
}

#endif
