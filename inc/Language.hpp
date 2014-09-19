
#ifndef MKSRC_LANGUAGE_HPP
#define MKSRC_LANGUAGE_HPP

#include <map>
#include <string>
#include <vector>

namespace mksrc {
    struct Language {
        typedef std::vector<std::string> StringList;
        typedef std::map<int, StringList> SuffixMap;
        typedef std::map<int, std::string> BodyFileMap;
        
        std::string shortname, longname;
        std::string doctype;
        SuffixMap suffix;
        std::string comment_line, comment_start, comment_fill, comment_end;
        std::string doc_line, doc_start, doc_fill, doc_end;
        BodyFileMap body;
        
        void addSuffix(int index, const std::string &suffix);
    };
    
    template <typename Insertable>
    Insertable & operator<<(Insertable &out,
                            const Language::SuffixMap &strmap)
    {
        out << "[";
        for(const std::pair<int, std::vector<std::string>> &pair : strmap) {
            const std::vector<std::string> &list = pair.second;
            auto len = list.size();
            out << pair.first << ":[";
            for(decltype(len) i = 0; i < len - 1; ++i) {
                out << "\"" << list[i] << "\", ";
            }
            out << "\"" << list[len - 1] << "\"],";
        }
        out << "]";
        return out;
    }
    
# define MKSRC_OUT_ASSIGN(name, strval) \
    "  " name " = \"" << strval << "\"\n"
    template <typename Insertable>
    Insertable & operator<<(Insertable &out, const Language &lang) {
        out << "language {\n" <<
            MKSRC_OUT_ASSIGN("short-name", lang.shortname) <<
            MKSRC_OUT_ASSIGN("long-name", lang.longname) <<
            "  suffix = " << lang.suffix << "\n" <<
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
