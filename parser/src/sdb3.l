%{
#include <iostream>
#include <string>
#include "Ket.h"
#include "Superposition.h"
#include "Sequence.h"
#include "sdb3.tab.h"

extern int yylex();
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%option noyywrap

digit					[0-9]

%%
[ \t]+					return TOKEN(TSPACE);
"\n"					return TOKEN(TENDL);
"--".*					return TOKEN(TCOMMENT);
"|context>"				return TOKEN(TCONTEXT_KET);
"supported-ops".*			return TOKEN(TSUPPORTED_OPS);
{digit}+\.{digit}*			SAVE_TOKEN; return TDOUBLE;
{digit}+				SAVE_TOKEN; return TINTEGER;
"|"[^<|>]*">"				SAVE_TOKEN; return TKET;
[a-zA-Z!][a-zA-Z0-9\-\+!?\.:]+		SAVE_TOKEN; return TOP_LABEL;
"\""[^\"\[\]<|>]*"\""			SAVE_TOKEN; return TPARAMETER_STR;
"|"					return TOKEN(TPIPE);
"+=>"					return TOKEN(TADD_LEARN_SYM);
".=>"					return TOKEN(TSEQ_LEARN_SYM);
"#=>"					return TOKEN(TSTORE_LEARN_SYM);
"!=>"					return TOKEN(TMEM_LEARN_SYM);
"=>"					return TOKEN(TLEARN_SYM);
"+"					return TOKEN(TPLUS);
"-"					return TOKEN(TMINUS);
"."					return TOKEN(TSEQ);
"__"					return TOKEN(TMERGE2);
"_"					return TOKEN(TMERGE);
">"					return TOKEN(TGT);
"<"					return TOKEN(TLT);
"("					return TOKEN(TLPAREN);
")"					return TOKEN(TRPAREN);
"["					return TOKEN(TLSQUARE);
"]"					return TOKEN(TRSQUARE);
"/"					return TOKEN(TDIVIDE);
","					return TOKEN(TCOMMA);
":"                                     return TOKEN(TCOLON);
"^"                                     return TOKEN(TPOW);
"\""                                    return TOKEN(TQUOTE);
"\*"                                    return TOKEN(TSTAR);
.					;

%%

