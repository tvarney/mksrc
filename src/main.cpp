
#include <iostream>
#include <string>

#include "MakeSourceState.hpp"
#include "ParserState.hpp"
#include "Util.hpp"

using namespace mksrc;

int main(int argc, char **argv) {
    MakeSourceState state;
    state.parse(argc, argv);
    std::string user_config = util::GetHomeDirectory() + ".mksrc/";
    std::string user_languages = util::Join(user_config, "lang/");
    std::string user_licenses = util::Join(user_config, "license/");
    
    ParserState parser;
    std::vector<std::string> files = util::ListDirectory("/etc/mksrc/lang/");
    util::ListDirectory(user_languages, files);
    for(const std::string &fname : files) {
        parser.parse(fname);
    }
    
    const std::map<std::string, Language> &languages = parser.languages();
    for(const std::pair<std::string, Language> &lang : languages) {
        std::cout << lang.second;
    }
    
    return 0;
}
