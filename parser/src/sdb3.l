%{
#include <iostream>
#include <string>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Sequence.h"
#include "BaseRule.h"
#include "NewContext.h"
#include "ContextList.h"
#include "BaseOp.h"
#include "OpSeq.h"
#include "SingleOpRule.h"
#include "OpRule.h"
#include "SelfKet.h"
#include "BracketOp.h"
#include "sdb3.tab.h"

int line_num = 1;

extern int yylex();
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

ulong get_ket_idx(char *str, yy_size_t len) { // tidy later!!
    std::string s(str, len);
    ulong idx = ket_map.get_idx(s.substr(1, s.size() - 2));
    return idx;
}

ulong get_op_idx(char *str, yy_size_t len) {
    std::string s(str, len);
    ulong idx = ket_map.get_idx(s);
    return idx;
}

%}

%option noyywrap

digit					[0-9]

%%
[ \t]+					return TOKEN(TSPACE);
"\n"					{ ++line_num; return TOKEN(TENDL); }
"--".*					return TOKEN(TCOMMENT);
"|context>"				return TOKEN(TCONTEXT_KET);
"|_self>"				return TOKEN(TSELF_KET);
"|_self"{digit}">"			{ yylval.token = yytext[6] - '0'; return TSELF_KETK; }
"supported-ops".*			return TOKEN(TSUPPORTED_OPS);
{digit}+\.{digit}*			{ yylval.d = atof(yytext); return TDOUBLE; }
{digit}+				{ yylval.u = atoll(yytext); return TINTEGER; }
"|"[^<|>]*">"				{ yylval.u = get_ket_idx(yytext, yyleng); return TKET; }
[a-zA-Z!][a-zA-Z0-9\-\+!?\.:]+		{ yylval.u = get_op_idx(yytext, yyleng); return TOP_LABEL; }
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

