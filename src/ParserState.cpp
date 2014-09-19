
#include "ParserState.hpp"

#include <iostream>
#include "language-parser.tab.hh"

using namespace mksrc;

ParserState::ParserState() :
    m_TraceScanning(false), m_TraceParsing(false),
    m_CurrentLanguage(nullptr)
{ }
ParserState::~ParserState() { }

Language & ParserState::create(const std::string &shortname) {
    m_CurrentLanguage = &(m_Languages[shortname]);
    m_CurrentLanguage->name = shortname;
    return *m_CurrentLanguage;
}

Language & ParserState::current() {
    static Language _s_scratch;
    if(m_CurrentLanguage == nullptr) {
        return _s_scratch;
    }
    return *m_CurrentLanguage;
}
std::map<std::string, Language> & ParserState::languages() {
    return m_Languages;
}
const std::map<std::string, Language> & ParserState::languages() const {
    return m_Languages;
}

int ParserState::parse(const std::string &fname) {
    m_FileName = fname;
    scan_begin();
    yy::language_parser parser(*this);
    parser.set_debug_level(m_TraceParsing);
    int res = parser.parse();
    scan_end();
    return res;
}

void ParserState::error(const yy::location &loc, const std::string &message) {
    std::cerr << loc << ": " << message << std::endl;
}
void ParserState::error(const std::string &message) {
    std::cerr << message << std::endl;
}

std::string & ParserState::file() {
    return m_FileName;
}

int ParserState::getSuffixIndex() const {
	return m_SuffixIndex;
}
void ParserState::setSuffixIndex(int index) {
	m_SuffixIndex = index;
}
