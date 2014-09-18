
#ifndef MKSRC_UTIL_HPP
#define MKSRC_UTIL_HPP

#include <string>

namespace mksrc {
    namespace util {
        std::string GetHomeDirectory();
        std::string GetEnv(const char *name);
    }
}

#endif
