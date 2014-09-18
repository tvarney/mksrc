
#include "Util.hpp"

// C++ headers
#include <cstdlib>
#include <sstream>
#include <stdexcept>

// C headers
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

using namespace mksrc;

std::string util::GetHomeDirectory() {
    const char *homestr = std::getenv("HOME");
    if(homestr == nullptr) {
        errno = 0;
        struct passwd *password = getpwuid(geteuid());
        if(errno != 0 || password == nullptr) {
            std::stringstream fmt("Could not get Home directory: errno = ");
            fmt << errno << " \"" << strerror(errno) << "\"";
            throw std::runtime_error(fmt.str());
        }
        homestr = password->pw_dir;
    }
    if(homestr == nullptr) {
        throw std::runtime_error("User has no Home directory");
    }
    return std::string(homestr);
}
