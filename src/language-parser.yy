/* -*- C++ -*- */

%skeleton "lalr1.cc"
%require "2.5"
%define parser_class_name "language_parser"

%code requires {
namespace mksrc {
    class ParserState;
}
}

%parse-param { mksrc::ParserState &state }
%lex-param   { mksrc::ParserState &state }

%locations
%initial-action {
    @$.begin.filename = @$.end.filename = &state.file();
}

%debug
%error-verbose

%union {
    int y_num;
    const char *y_str;
}

%code {
# include "ParserState.hpp"
}

%token END 0 "end of file"
%token ASSIGN "="
%token APPEND "+="
%token LIST_SEP ","
%token OPEN_LIST "["
%token CLOSE_LIST "]"
%token OPEN_SCOPE "{"
%token CLOSE_SCOPE "}"
%token STATEMENT_END ";"
%token NUMBER "number"
%token STRING "string"
%token BOOLEAN "bool"
%token LANGUAGE "language"
%token ERROR "ERROR"
%token DESCRIPTION "description"
%token SUFFIXES "suffix"
%token COMMENT_LINE "comment-line"
%token COMMENT_START "comment-start"
%token COMMENT_FILL "comment-fill"
%token COMMENT_END "comment-end"
%token DOC_LINE "doc-line"
%token DOC_START "doc-start"
%token DOC_FILL "doc-fill"
%token DOC_END "doc-end"

%%

file:
  | file language
  ;

language:
    LANGUAGE STRING {
        state.create(yylval.y_str);
    } OPEN_SCOPE lang_assignment CLOSE_SCOPE
    ;


lang_assignment:
  | lang_assignment assignment_type STATEMENT_END
  | lang_assignment assignment_type
  ;

assignment_type:
    DESCRIPTION ASSIGN STRING {
        state.current().description = yylval.y_str;
    }
  | lang_suffixes
  | lang_comment
  | lang_doc
    ;

lang_suffixes:
    SUFFIXES suffix_index suffix_assignment OPEN_LIST suffix_list CLOSE_LIST
    ;

suffix_index:
    OPEN_LIST NUMBER {
        state.setSuffixIndex(yylval.y_num);
    } CLOSE_LIST
  | {
        state.setSuffixIndex(0);
    }
    ;

suffix_assignment:
    APPEND
  | ASSIGN {
        state.current().suffix[state.getSuffixIndex()].clear();
    }
    ;

suffix_list:
    suffix_list LIST_SEP STRING {
        state.current().addSuffix(state.getSuffixIndex(), yylval.y_str);
    }
  | STRING {
        state.current().addSuffix(state.getSuffixIndex(), yylval.y_str);
    }
    ;

lang_comment:
    COMMENT_LINE ASSIGN STRING {
        state.current().comment_line = yylval.y_str;
    }
  | COMMENT_START ASSIGN STRING {
        state.current().comment_start = yylval.y_str;
    }
  | COMMENT_FILL ASSIGN STRING {
        state.current().comment_fill = yylval.y_str;
    }
  | COMMENT_END ASSIGN STRING {
        state.current().comment_end = yylval.y_str;
    }
    ;

lang_doc:
    DOC_LINE ASSIGN STRING {
        state.current().doc_line = yylval.y_str;
    }
  | DOC_START ASSIGN STRING {
        state.current().doc_start = yylval.y_str;
    }
  | DOC_FILL ASSIGN STRING {
        state.current().doc_fill = yylval.y_str;
    }
  | DOC_END ASSIGN STRING {
        state.current().doc_end = yylval.y_str;
    }
    ;

%%

void yy::language_parser::error(const yy::language_parser::location_type &loc,
                                const std::string &message)
{
    state.error(loc, message);
}
