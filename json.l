%{

#include "json.tab.h"
#include <stdio.h>
#include <string.h>

#include "json_ast.hpp"
using namespace json_ast;


int countWord=0;
int lineNumber=1;
int colNumber=1;
%}

SPACE    \r|\t|" "
STRING \"([^"]|\\\")*\"
NUMBER ([0-9])+
DECIMAL {NUMBER}\.{NUMBER}
WHITESPACE {SPACE}+
chars [A-Za-z]*
%%

\[ {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_LEFT_BRACKET;}
\] {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_RIGHT_BRACKET;}
\{ {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_LEFT_BRACE;}
\} {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_RIGHT_BRACE;}
,  {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_COMMA;}
:  {colNumber+=yyleng ;/*puts(yytext); yylval=strdup(yytext);*/ return TT_COLON;}
"\n" {lineNumber+=1 ; colNumber=1; }
{STRING} {colNumber+=yyleng ;/*puts(yytext);*/ yylval=CreateString(yytext,yyleng); return TT_STRING;}
{NUMBER} {colNumber+=yyleng ;/*puts(yytext);*/ yylval=CreateString(yytext,yyleng); return TT_INT;}
{DECIMAL} {colNumber+=yyleng;/*puts(yytext);*/ yylval=CreateString(yytext,yyleng); return TT_DOUBLE;}
{WHITESPACE} { colNumber+=yyleng ;  /**do nothing*/}
. {printf("unexpected token\n"); return TT_ERROR;}
%%

int yyerror(char *msg);
int yywrap(){
  return 1;
}