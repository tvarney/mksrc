
#include "ParserState.hpp"

#include <iostream>
#include "language-parser.tab.hh"

using namespace mksrc;

ParserState::ParserState() :
    m_TraceScanning(false), m_TraceParsing(false)
{ }
ParserState::~ParserState() { }

Language & ParserState::create() {
    std::cerr << "Creating new language" << std::endl;
    m_Languages.emplace_back();
    return current();
}
Language & ParserState::current() {
    return m_Languages.back();
}
std::vector<Language> & ParserState::languages() {
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
