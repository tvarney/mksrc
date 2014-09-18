
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
    
    template <typename Insertable>
    Insertable & operator<<(Insertable &out,
                            const std::vector<std::string> &strlist)
    {
        out << "[";
        auto len = strlist.size();
        for(decltype(len) i = 0; i < len - 1; ++i) {
            out << "\"" << strlist[i] << "\", ";
        }
        out << "\"" << strlist[len - 1] << "\"]";
        return out;
    }
    
# define MKSRC_OUT_ASSIGN(name, strval) \
    "  " name " = \"" << strval << "\"\n"
    template <typename Insertable>
    Insertable & operator<<(Insertable &out, const Language &lang) {
        out << "language {\n" <<
            MKSRC_OUT_ASSIGN("short-name", lang.shortname) <<
            MKSRC_OUT_ASSIGN("long-name", lang.longname) <<
            "  suffix = " << lang.suffixes << "\n" <<
            MKSRC_OUT_ASSIGN("comment-line", lang.comment_line) <<
            MKSRC_OUT_ASSIGN("comment-start", lang.comment_start) << 
            MKSRC_OUT_ASSIGN("comment-fill", lang.comment_fill) <<
            MKSRC_OUT_ASSIGN("comment-end", lang.comment_end) <<
            MKSRC_OUT_ASSIGN("doc-line", lang.doc_line) <<
            MKSRC_OUT_ASSIGN("doc-start", lang.doc_start) <<
            MKSRC_OUT_ASSIGN("doc-fill", lang.doc_fill) <<
            MKSRC_OUT_ASSIGN("doc-end", lang.doc_end) <<
            "}\n";
        return out;
    }
}

#endif
