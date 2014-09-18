
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "ParserState.hpp"

void yyerror(const char *);
extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

%}

%token T_INTEGER T_STRING T_BOOLEAN
%token T_LANGUAGE
%token T_SHORTNAME T_LONGNAME T_SUFFIXES
%token T_COMMENT_LINE T_DOC_LINE
%token T_COMMENT_START T_COMMENT_FILL T_COMMENT_END
%token T_DOC_START T_DOC_FILL T_DOC_END

%union {
    char *y_str;
    int y_num;
}

%%

file:
    file language
  | language
  ;

language:
    T_LANGUAGE '{' {
        mksrc::parser_state.languages.emplace_back();
    } lang_assignment '}'
    ;


lang_assignment:
    lang_name lang_assignment ';'
  | lang_suffixes lang_assignment ';'
  | lang_comment lang_assignment ';'
  | lang_doc lang_assignment ';'
  | 
    ;

lang_name:
    T_SHORTNAME '=' T_STRING {
        mksrc::parser_state.languages.back().shortname = yylval.y_str;
    }
  | T_LONGNAME '=' T_STRING {
      mksrc::parser_state.languages.back().longname = yylval.y_str;
    }
    ;

lang_suffixes:
    T_SUFFIXES '=' '[' suffix_list ']'
    ;

suffix_list:
    suffix_list ',' T_STRING {
        mksrc::parser_state.languages.back().suffixes.push_back(yylval.y_str);
    }
  | T_STRING {
      mksrc::parser_state.languages.back().suffixes.push_back(yylval.y_str);
    }
    ;

lang_comment:
    T_COMMENT_LINE '=' T_STRING {
        mksrc::parser_state.languages.back().comment_line = yylval.y_str;
    }
  | T_COMMENT_START '=' T_STRING {
      mksrc::parser_state.languages.back().comment_start = yylval.y_str;
    }
  | T_COMMENT_FILL '=' T_STRING {
      mksrc::parser_state.languages.back().comment_fill = yylval.y_str;
    }
  | T_COMMENT_END '=' T_STRING {
      mksrc::parser_state.languages.back().comment_end = yylval.y_str;
    }
    ;

lang_doc:
    T_DOC_LINE '=' T_STRING {
        mksrc::parser_state.languages.back().doc_line = yylval.y_str;
    }
  | T_DOC_START '=' T_STRING {
      mksrc::parser_state.languages.back().doc_start = yylval.y_str;
    }
  | T_DOC_FILL '=' T_STRING {
      mksrc::parser_state.languages.back().doc_fill = yylval.y_str;
    }
  | T_DOC_END '=' T_STRING {
      mksrc::parser_state.languages.back().doc_end = yylval.y_str;
    }
    ;

%%

void yyerror(const char *message) {
    std::cerr << message << std::endl;
}
