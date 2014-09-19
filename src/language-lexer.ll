/* -*- C++ -*- */
%{
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <string>
#include "ParserState.hpp"
#include "language-parser.tab.hh"

#undef yywrap
#define yywrap() 1
#define yyterminate() return token::END
%}

%option noyywrap nounput batch debug

int [0-9]+
id [a-zA-Z][a-zA-Z_\-0-9]*
blank [ \t]

%{
# define YY_USER_ACTION yyloc->columns(yyleng);
%}

%%

%{
    yyloc->step();
%}

{blank}+ { yyloc->step(); }
[\n]+    { yyloc->lines(yyleng); yyloc->step(); }

%{
    typedef yy::language_parser::token token;
%}

#.*\n //Comment

"=" return token::ASSIGN;
"," return token::LIST_SEP;
"[" return token::OPEN_LIST;
"]" return token::CLOSE_LIST;
"{" return token::OPEN_SCOPE;
"}" return token::CLOSE_SCOPE;
";" return token::STATEMENT_END;

"language"      return token::LANGUAGE;
"description"   return token::DESCRIPTION;
"suffix"        return token::SUFFIXES;
"comment-line"  return token::COMMENT_LINE;
"comment-start" return token::COMMENT_START;
"comment-fill"  return token::COMMENT_FILL;
"comment-end"   return token::COMMENT_END;
"doc-line"      return token::DOC_LINE;
"doc-start"     return token::DOC_START;
"doc-fill"      return token::DOC_FILL;
"doc-end"       return token::DOC_END;

\"((\\.)|[^\\\"\n])* {
    state.error(*yyloc, "Unclosed string literal");
}
\"((\\.)|[^\\\"\n])*\" {
    yytext[yyleng - 1] = '\0';
    yylval->y_str = yytext + 1;
    return token::STRING;
}

{int} {
    errno = 0;
    long n = strtol(yytext, NULL, 10);
    if(!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        state.error(*yyloc, "Integer is out of range");
        return token::ERROR;
    }
    yylval->y_num = n;
    return token::NUMBER;
}

{id} {
    state.error(*yyloc, std::string("Invalid identifier: ") + yytext);
    return token::ERROR;
}

. state.error(*yyloc, "Invalid character"); return token::ERROR;

%%

void mksrc::ParserState::scan_begin() {
    yy_flex_debug = m_TraceScanning;
    if(m_FileName == "-") {
        yyin = stdin;
    }else if (!(yyin = fopen(m_FileName.data(), "r"))) {
        error(std::string("Cannot open") + m_FileName);
        return;
    }
}

void mksrc::ParserState::scan_end() {
    if(m_FileName != "-") {
        fclose(yyin);
    }
}
