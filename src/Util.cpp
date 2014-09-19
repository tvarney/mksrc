
#include "Util.hpp"

// C++ headers
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include <iostream>

// C headers
#include <dirent.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

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
    int len;
    for(len = 0; homestr[len] != '\0'; ++len) { }
    
    return ((homestr[len - 1] == '/') ?
            std::string(homestr) :
            std::string(homestr) + "/");
}

std::string util::GetEnv(const char *name) {
    const char *value = std::getenv(name);
    return ((value == nullptr) ? std::string() : std::string(value));
}

std::string util::Join(const std::string &front, const std::string &back) {
    return ((front[front.size() - 1] == '/') ?
            (front + back) : ((front + "/") + back));
}

std::vector<std::string> util::ListDirectory(const std::string &dirname) {
    std::vector<std::string> files;
    DIR *dir = opendir(dirname.data());
    if(dir != nullptr) {
        dirent *entry;
        while((entry = readdir(dir)) != nullptr) {
            if(strcmp(".", entry->d_name) != 0 &&
               strcmp("..", entry->d_name) != 0)
                {
                    files.emplace_back(util::Join(dirname, entry->d_name));
                }
        }
    }
    return files;
}

std::size_t util::ListDirectory(const std::string &dirname,
                                std::vector<std::string> &file_list)
{
    std::size_t added = 0;
    DIR *dir = opendir(dirname.data());
    if(dir != nullptr) {
        dirent *entry;
        while((entry = readdir(dir)) != nullptr) {
            if(strcmp(".", entry->d_name) != 0 &&
               strcmp("..", entry->d_name) != 0)
                {
                    file_list.emplace_back(util::Join(dirname, entry->d_name));
                    added += 1;
                }
        }
    }
    return added;
}
