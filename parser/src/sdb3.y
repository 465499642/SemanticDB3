%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
%}

%union {
    std::string *string;
    int token;
}

%token <string> TINTEGER TDOUBLE TKET TOP_LABEL TPARAMETER
%token <token> TADD_LEARN_SYM TSEQ_LEARN_SYM TSTORE_LEARN_SYM TMEM_LEARN_SYM TLEARN_SYM
%token <token> TPLUS TMINUS TSEQ TMERGE2 TMERGE TDIVIDE
%token <token> TPIPE TGT TLT TLPAREN TRPAREN TLSQUARE TRSQUARE TENDL TSPACE
%token <token> TCOMMENT TSUPPORTED_OPS TCONTEXT_PREFIX

%type <string> rule ket int double op

%start rule

%%

rule: 
    | double endl
    | int endl
    | ket endl
    | op endl
    ;

int:  TINTEGER { std::cout << "bison found an int: " << $1 << std::endl; }
    ;

double: TDOUBLE { 
        std::cout << "bison found a double: " << $1 << std::endl; 
        }
    ;

ket:    TKET {
        std::cout << "bison found a ket: " << $1 << std::endl;
        }
    ;

op:     TOP_LABEL { std::cout << "bison found an op-label: " << $1 << std::endl; }
    ;

endl:    TENDL
    |    endl TENDL
    ;

%%

int main(int argc, char** argv) {
    yyin = stdin;
    do {
        yyparse();
    } while(!feof(yyin));
    return 0;
}
