
#ifndef MKSRC_UTIL_HPP
#define MKSRC_UTIL_HPP

#include <string>
#include <vector>

namespace mksrc {
    namespace util {
        std::string GetHomeDirectory();
        std::string GetEnv(const char *name);
        std::string Join(const std::string &front, const std::string &back);
        std::size_t ListDirectory(const std::string &
                                  std::vector<std::string> &file_list);
        std::vector<std::string> ListDirectory(const std::string &dirname);
    }
}

#endif
