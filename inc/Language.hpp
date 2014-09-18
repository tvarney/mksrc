
#ifndef MKSRC_LANGUAGE_HPP
#define MKSRC_LANGUAGE_HPP

#include <string>
#include <vector>

namespace mksrc {
    struct Language {
        std::string shortname, longname;
        std::string doctype;
        std::vector<std::string> suffixes;
        std::string comment_line, comment_start, comment_fill, comment_end;
        std::string doc_line, doc_start, doc_fill, doc_end;
    };
}

#endif
