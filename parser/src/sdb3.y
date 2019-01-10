%{
    #include <iostream>
    extern int yylex();
    extern int yyparse();
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
%}

%union {
    std::string *string;
    int token;
}

%token <string> TCONTEXT_RULE TINTEGER TDOUBLE TKET_LABEL
%token <token> TADD_LEARN_SYM TSEQ_LEARN_SYM TSTORE_LEARN_SYM TMEM_LEARN_SYM TLEARN_SYM
%token <token> TPLUS TMINUS TSEQ TMERGE2 TMERGE
%token <token> TPIPE TGT TLT TLPAREN TRPAREN TENDL
%token <token> TCOMMENT TSUPPORTED_OPS

%start rule

%%
rule:
    rule TINTEGER endl { std::cout << "bison found an int: " << $2 << std::endl; }
    | rule TDOUBLE endl { std::cout << "bison found a double: " << $2 << std::endl; }
    | TINTEGER endl { std::cout << "bison found an int: " << $1 << std::endl; }
    | TDOUBLE endl { std::cout << "bison found a double: " << $1 << std::endl; }
    ;

endl:    TENDL
     |   endl TENDL
     ;
%%

int main(int argc, char** argv) {
    yyparse();
}
