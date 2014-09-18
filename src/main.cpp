
#include <iostream>
#include <string>

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include "MakeSourceState.hpp"
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
    
    std::vector<std::string> files = util::ListDirectory(user_languages);
    if(files.size() == 0) {
        std::cout << "No Language Files" << std::endl;
    }else {
        std::cout << "Language Files:" << std::endl;
        for(std::string &file : files) {
            std::cout << "  " << file << std::endl;
        }
    }
    return 0;
}
