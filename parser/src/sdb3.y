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

%token <string> TINTEGER TDOUBLE TKET_LABEL
%token <token> TADD_LEARN_SYM TSEQ_LEARN_SYM TSTORE_LEARN_SYM TMEM_LEARN_SYM TLEARN_SYM
%token <token> TPLUS TMINUS TSEQ TMERGE2 TMERGE
%token <token> TPIPE TGT TLT TLPAREN TRPAREN TENDL
%token <token> TCOMMENT TSUPPORTED_OPS TCONTEXT_PREFIX

%type <string> rule ket int double context_line

%start rule

%%

rule: 
    double endl
    | int endl
    | context_line endl
    | ket endl
    ;

int:    TINTEGER { 
        std::cout << "bison found an int: " << $1 << std::endl; 
        }
    ;

double: TDOUBLE { 
        std::cout << "bison found a double: " << $1 << std::endl; 
        }
    ;

ket:    TPIPE TKET_LABEL TGT {
        std::cout << "bison found a ket label: " << $2 << std::endl;
        }
    ;

context_line: TCONTEXT_PREFIX TKET_LABEL TGT {
        std::cout << "bison found a context label: " << $2 << std::endl;
        }
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
