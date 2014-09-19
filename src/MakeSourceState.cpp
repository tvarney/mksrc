
#include "MakeSourceState.hpp"

#include <cstdio>
#include <iostream>
#include <getopt.h>

#include "Util.hpp"

using namespace mksrc;

static const char * g_NoLicense = "none";
static const char * g_DefaultDocstyle = "default";

static const char *short_options = "vbqL:D:B:";
static struct option long_options[] = {
    {"verbose", no_argument, nullptr, 'v'},
    {"brief", no_argument, nullptr, 'b'},
    {"quiet", no_argument, nullptr, 'q'},
    {"license", required_argument, nullptr, 'L'},
    {"docstyle", required_argument, nullptr, 'D'},
    {"body", required_argument, nullptr, 'B'},
};

MakeSourceState::MakeSourceState() {
    m_LicenseName = g_NoLicense;
    m_DocstyleName = g_DefaultDocstyle;
    m_DoBody = true;
}

bool MakeSourceState::parse(int argc, char **argv) {
    int option_ind = 0, c;
    while(true) {
        c = getopt_long(argc, argv, short_options, long_options, &option_ind);
        if(c == -1) {
            break;
        }
        
        switch(c) {
        case 'v':
            m_OutputLevel = OutputLevel::Verbose;
            break;
        case 'b':
            m_OutputLevel = OutputLevel::Brief;
            break;
        case 'q':
            m_OutputLevel = OutputLevel::Quiet;
            break;
        case 'L':
            m_LicenseName = optarg;
            break;
        case 'D':
            m_DocstyleName = optarg;
            break;
        case 'B':
            m_DoBody = false;
            break;
        default:
            return false;
        }
    }
    
    for(int i = optind; i < argc; ++i) {
        m_FileNames.push_back(argv[i]);
    }
    
    return true;
}

bool MakeSourceState::parse(const char * filename) {
    return false;
}

bool MakeSourceState::parse_languages(const std::string &directory) {
    std::vector<std::string> files = util::ListDirectory(directory);
    for(const std::string &filename : files) {
        m_Parser.parse(filename);
    }
    return true;
}

void MakeSourceState::report_languages() const {
    auto &languages = m_Parser.languages();
    for(auto &pairs : languages) {
        std::cout << pairs.second << std::endl;
    }
}

void MakeSourceState::create_files() {
    for(const std::string &fname : m_FileNames) {
        const char *ext = util::GetExtension(fname.data());
        std::cout << "Filename: \"" << fname << "\" -> \"" <<
            (ext == nullptr ? "none" : ext) << "\"" << std::endl;
    }
}
