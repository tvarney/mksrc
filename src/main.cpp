
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
    
    state.parse_languages("/etc/mksrc/lang/");
    state.parse_languages(user_languages);
    
    state.report_languages();
    
    return 0;
}
