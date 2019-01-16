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

%token <string> TINTEGER TDOUBLE TKET TOP_LABEL TPARAMETER_STR
%token <token> TADD_LEARN_SYM TSEQ_LEARN_SYM TSTORE_LEARN_SYM TMEM_LEARN_SYM TLEARN_SYM
%token <token> TPLUS TMINUS TSEQ TMERGE2 TMERGE TDIVIDE TCOMMA TCOLON TPOW
%token <token> TPIPE TGT TLT TLPAREN TRPAREN TLSQUARE TRSQUARE TENDL TSPACE
%token <token> TCOMMENT TSUPPORTED_OPS TCONTEXT_KET

%type <string> swfile rule numeric ket coeff_ket simple_op compound_op function_op general_op parameter_string parameter parameters
%type <string> sp_parameters literal_sequence powered_op op op_sequence

%start swfile

%%

swfile : %empty { $$ = new std::string(); }
       | swfile rule endl { $$ = $2; }
       ;

rule : space comment { $$ = new std::string(); std::cout << "comment" << std::endl; }
     | space TCONTEXT_KET space TLEARN_SYM space ket { std::cout << "context learn rule" << std::endl; }
     | space TSUPPORTED_OPS { std::cout << "supported-ops learn rule" << std::endl; }
     | space simple_op space coeff_ket space learn_sym space literal_sequence { std::cout << "learn rule" << std::endl; }
     | numeric { $$ = $1; std::cout << "numeric: " << *$1 << std::endl; }
     | literal_sequence { }
     | coeff_ket { $$ = $1; std::cout << "ket" << std::endl; }
     | space { std::cout << "space" << std::endl; }
     | learn_sym { }
     | parameter_string { $$ = $1; }
     | TCOLON op_sequence { }
     ;


numeric : TINTEGER { $$ = $1; std::cout << "int: " << *$1 << std::endl; }
        | TDOUBLE { $$ = $1; std::cout << "double: " << *$1 << std::endl; }
        ;

ket : TKET { $$ = $1; std::cout << "ket: " << *$1 << std::endl; }
    ;

coeff_ket : ket { $$ = $1; }
          | numeric space ket { $$ = $3; std::cout << "coeff_ket: " << *$1 << *$3 << std::endl; }
          ;

literal_sequence : coeff_ket { $$ = $1; }
              | literal_sequence space op_symbol space coeff_ket { $$ = $5; std::cout << "seq: " << *$1 << *$5 << std::endl; }
              ;

op_symbol : TPLUS
          | TMINUS
          | TSEQ
          | TMERGE2 
          | TMERGE
          ;

simple_op : TOP_LABEL { $$ = $1; std::cout << "simple op: " << *$1 << std::endl; }
          ;

parameter_string : TPARAMETER_STR { $$ = $1; std::cout << "parameter string: " << *$1 << std::endl; }
                 ;

parameter : numeric { $$ = $1; }
          | simple_op { $$ = $1; }
          | parameter_string { $$ = $1; }
          ;

parameters : parameter { $$ = $1; }
           | parameters TCOMMA space parameter { $$ = $4; std::cout << "parameters: " << *$1 << " " << *$4 << std::endl; }
           ;

compound_op : simple_op TLSQUARE parameters TRSQUARE { $$ = $1; std::cout << "compound_op: " << *$1 << "[ " << *$3 << " ]" << std::endl; }
            ;

sp_parameters : space literal_sequence space { $$ = $2; }
              | sp_parameters TCOMMA space literal_sequence space { $$ = $4; }
              ;

function_op : simple_op TLPAREN sp_parameters TRPAREN { $$ = $1; std::cout << "function_op: " << *$1 << "( " << *$3 << " )" << std::endl; }
            ;

general_op : simple_op { $$ = $1; }
           | compound_op { $$ = $1; }
           | function_op { $$ = $1; }
           ;

powered_op : general_op TPOW TINTEGER { $$ = $1; std::cout << "powered_op: " << *$1 << "^" << *$3 << std::endl; }
           ;

op : powered_op { $$ = $1; }
   | general_op { $$ = $1; }
   ;

op_sequence : op { $$ = $1; }
            | op_sequence TSPACE op { $$ = $1; std::cout << "op_sequence: " << *$1 << " " << *$3 << std::endl; }
            ;

comment : TCOMMENT { std::cout << "TCOMMENT" << std::endl; }
        ;

learn_sym : TLEARN_SYM { std::cout << "TLEARN_SYM" << std::endl; }
          | TADD_LEARN_SYM { std::cout << "TADD_LEARN_SYM" << std::endl; }
          | TSEQ_LEARN_SYM { std::cout << "TSEQ_LEARN_SYM" << std::endl; }
          | TSTORE_LEARN_SYM { std::cout << "TSTORE_LEARN_SYM" << std::endl; }
          | TMEM_LEARN_SYM { std::cout << "TMEM_LEARN_SYM" << std::endl; }
          ;

space : %empty { std::cout << "EMPTY" << std::endl; }
      | TSPACE { std::cout << "TSPACE" << std::endl; }
      ;

endl:    TENDL { std::cout << "TENDL" << std::endl; }
    |    endl TENDL
    ;

%%

int main(int argc, char** argv) {
    yyparse();
    return 0;
}
