%{
    #include <iostream>
    #include "sdb3.tab.h"

    extern int yylex();
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
%}
%option noyywrap
%%
[ \t]                                 ;
"\n"                                  return TOKEN(TENDL);
"-- ".*                               return TOKEN(TCOMMENT);
[ ]*"|context> => |context: ".*">"    SAVE_TOKEN; return TCONTEXT_RULE;
[ ]*"supported-ops |".*               return TOKEN(TSUPPORTED_OPS);
[0-9]+\.[0-9]+                        SAVE_TOKEN; return TDOUBLE;
[0-9]+                                SAVE_TOKEN; return TINTEGER;
"|"                                   return TOKEN(TPIPE);
"+=>"                                 return TOKEN(TADD_LEARN_SYM);
".=>"                                 return TOKEN(TSEQ_LEARN_SYM);
"#=>"                                 return TOKEN(TSTORE_LEARN_SYM);
"!=>"                                 return TOKEN(TMEM_LEARN_SYM);
"=>"                                  return TOKEN(TLEARN_SYM);
"+"                                   return TOKEN(TPLUS);
"-"                                   return TOKEN(TMINUS);
"."                                   return TOKEN(TSEQ);
"__"                                  return TOKEN(TMERGE2);
"_"                                   return TOKEN(TMERGE);
">"                                   return TOKEN(TGT);
"<"                                   return TOKEN(TLT);
"("                                   return TOKEN(TLPAREN);
")"                                   return TOKEN(TRPAREN);
[^<|>]+                               SAVE_TOKEN; return TKET_LABEL;
.                                     ;
%%

