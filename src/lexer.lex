
%{
#include <stdlib.h>
#include "parser.tab.h"
%}

%option nounput

%%

true {
    yylval.y_num = 1;
    return T_BOOLEAN;
}
false {
    yylval.y_num = 0;
    return T_BOOLEAN;
}
on {
    yylval.y_num = 1;
    return T_BOOLEAN;
}
off {
    yylval.y_num = 0;
    return T_BOOLEAN;
}
yes {
    yylval.y_num = 1;
    return T_BOOLEAN;
}
no {
    yylval.y_num = 0;
    return T_BOOLEAN;
}

shortname { return T_SHORTNAME; }
longname  { return T_LONGNAME; }

comment-line  { return T_COMMENT_LINE; }
comment-start { return T_COMMENT_START; }
comment-fill  { return T_COMMENT_FILL; }
comment-end   { return T_COMMENT_END; }

doc-line  { return T_DOC_LINE; }
doc-start { return T_DOC_START; }
doc-fill  { return T_DOC_FILL; }
doc-end   { return T_DOC_END; }

suffix  { return T_SUFFIXES; }

#[^\n]*\n ;

\"([^\\\n]|(\\.))*\" {
    yylval.y_str = yytext;
    return T_STRING;
}

[ \r\t\n]

%%

int yywrap() {
    return 0;
}
