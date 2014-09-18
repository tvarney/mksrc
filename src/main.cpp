
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
    std::cout << "User Config Directory: \"" << user_config << "\"" <<
        std::endl;
    
    std::string user_languages = util::Join(user_config, "lang/");
    std::cout << "User Language Directory: \"" << user_languages << "\"" <<
        std::endl;
    
    std::string user_licenses = util::Join(user_config, "license/");
    std::cout << "User License Directory: \"" << user_licenses << "\"" <<
        std::endl;
    
    ParserState parser;
    std::vector<std::string> files = util::ListDirectory("/etc/mksrc/lang/");
    util::ListDirectory(user_languages, files);
    for(const std::string &fname : files) {
        parser.parse(fname);
    }
    
    const std::vector<Language> &languages = parser.languages();
    for(const Language &lang : languages) {
        std::cout << lang;
    }
    
    return 0;
}
