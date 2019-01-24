%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "Ket.h"
    #include "Superposition.h"
    #include "Sequence.h"
    #include "NewContext.h"
    #include "ContextList.h"
    #include "BaseOp.h"
    #include "SimpleOp.h"
    #include "NumericOp.h"
    #include "PoweredOp.h"
    #include "OpSeq.h"
    #include "BaseCompoundSeq.h"
    #include "SingleCompoundSeq.h"
    #include "CompoundSeq.h"

    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
    std::string tidy_ket(const std::string &s) { std::string result = s.substr(1, s.size() - 2); return result; } // improve later!
%}

%union {
    std::string *string;
    ContextList *context;
    Ket *k;
    Superposition *sp;
    Sequence *seq;
    int token;
    double d;
    BaseOp *base_op;
    OpSeq *op_seq;
    BaseCompoundSeq *base_compound_seq;
    SingleCompoundSeq *single_compound_seq;
    CompoundSeq *compound_seq;
}

%token <string> TINTEGER TDOUBLE TKET TOP_LABEL TPARAMETER_STR
%token <token> TADD_LEARN_SYM TSEQ_LEARN_SYM TSTORE_LEARN_SYM TMEM_LEARN_SYM TLEARN_SYM
%token <token> TPLUS TMINUS TSEQ TMERGE2 TMERGE TDIVIDE TCOMMA TCOLON TPOW TQUOTE TSTAR
%token <token> TPIPE TGT TLT TLPAREN TRPAREN TLSQUARE TRSQUARE TENDL TSPACE
%token <token> TCOMMENT TSUPPORTED_OPS TCONTEXT_KET

%type <string> rule ket coeff_ket simple_op compound_op function_op general_op parameter_string parameter parameters
%type <string> sp_parameters literal_sequence powered_op op op_sequence bracket_ops symbol_op_sequence
%type <string> context_learn_rule
%type <context> swfile learn_rule
%type <k> real_ket
%type <d> numeric fraction
%type <seq> real_seq
%type <base_op> real_general_op real_powered_op real_op
%type <op_seq> real_op_sequence
%type <single_compound_seq> real_single_compound_seq 
%type <compound_seq> real_compound_seq

%start start

%%

start : swfile { $1->print_multiverse(); }
      ;

swfile : %empty { $$ = new ContextList("global context"); }
       | swfile comment { $1->print_multiverse(); } endl
       | swfile context_learn_rule endl { $1->set(*$2); }
       | swfile space TSUPPORTED_OPS endl { }
       | swfile space simple_op space ket space TLEARN_SYM space real_seq endl { $1->learn(*$3, *$5, $9); }
       | swfile space simple_op space ket space TADD_LEARN_SYM space real_seq endl { $1->add_learn(*$3, *$5, $9); }
       | swfile space simple_op space ket space TSEQ_LEARN_SYM space real_seq endl { $1->seq_learn(*$3, *$5, $9); }
       | swfile space simple_op space ket space TSTORE_LEARN_SYM space real_op_sequence space real_ket endl { 
           Sequence *k_seq = new Sequence(*$11);
           Sequence *seq = new Sequence($9->Compile(*$1, *k_seq));
           $1->learn(*$3, *$5, seq); 
       }
       | swfile space simple_op space ket space TMEM_LEARN_SYM space real_compound_seq endl {
           Sequence *seq = new Sequence($9->Compile(*$1));
           $1->learn(*$3, *$5, seq);
       }
       ;

learn_rule : space comment { }
           | context_learn_rule { $$ = $1; }
           | space TSUPPORTED_OPS { }
           | space simple_op space ket space learn_sym space ket { /* $$->learn(*$2, *$4, *$8); */ }
           ;

rule : space comment { $$ = new std::string(); std::cout << "comment" << std::endl; }
     | numeric { std::cout << "numeric: " << $1 << std::endl; }
     | real_seq { std::cout << "real seq: " << $1->to_string() << std::endl; }
     | literal_sequence { }
     | coeff_ket { $$ = $1; std::cout << "ket" << std::endl; }
     | space { std::cout << "space" << std::endl; }
     | learn_sym { }
     | parameter_string { $$ = $1; }
     | TCOLON op_sequence { }
     ;

context_learn_rule : space TCONTEXT_KET space TLEARN_SYM space ket { $$ = $6; }
                   ;

numeric : TINTEGER { $$ = std::stod(*$1); std::cout << "int: " << *$1 << std::endl; }
        | TDOUBLE { $$ = std::stod(*$1); std::cout << "double: " << *$1 << std::endl; }
        ;

fraction : numeric { $$ = $1; }
         | numeric TDIVIDE numeric { $$ = $1 / $3; std::cout << "fraction: " << $1 << "/" << $3 << std::endl; }
         ;

real_ket : ket { $$ = new Ket(*$1); }
         | TMINUS space numeric space ket { $$ = new Ket(*$5, - $3); }
         | numeric space ket { $$ = new Ket(*$3, $1); }
         ;

real_seq : real_ket { $$ = new Sequence(*$1); }
        | real_seq space TPLUS space real_ket { $1->add(*$5); } 
        | real_seq space TMINUS space real_ket { Ket tmp = *$5; tmp.multiply(-1); $1->add(tmp); }
        | real_seq space TSEQ space real_ket { $1->append(*$5); }
        | real_seq space TMERGE space real_ket { Sequence tmp(*$5); $1->merge(tmp); }
        | real_seq space TMERGE2 space real_ket { Sequence tmp(*$5); $1->merge(tmp, " "); }
        ;

real_general_op : simple_op { $$ = new SimpleOp(*$1); }
                | fraction { $$ = new NumericOp($1); }
                ;

real_powered_op : real_general_op TPOW TINTEGER { ulong pow = std::stoul(*$3); $$ = new PoweredOp($1, pow); }
                ;

real_op : real_powered_op { $$ = $1; }
        | real_general_op { $$ = $1; }
        ;

real_op_sequence : real_op { $$ = new OpSeq($1); }
                 | space TPLUS space real_op { $$ = new OpSeq(SPLUS, $4); }
                 | space TMINUS space real_op { $$ = new OpSeq(SMINUS, $4); }
                 | space TSEQ space real_op { $$ = new OpSeq(SSEQ, $4); }
                 | space TMERGE space real_op { $$ = new OpSeq(SMERGE, $4); }
                 | space TMERGE2 space real_op { $$ = new OpSeq(SMERGE2, $4); }
                 | real_op_sequence TSPACE real_op { $1->append($3); }
                 ;

real_single_compound_seq : real_op_sequence space real_ket { $$ = new SingleCompoundSeq($1, $3); }
                         | real_op_sequence space TLPAREN space real_seq space TRPAREN { $$ = new SingleCompoundSeq($1, $5); }
                         ;

real_compound_seq : real_single_compound_seq { $$ = new CompoundSeq(); $$->append(*$1); }
                  | real_compound_seq TSPACE real_single_compound_seq { $1->append(*$3); }
                  ;

ket : TKET { $$ = new std::string(tidy_ket(*$1)); std::cout << "ket: " << *$1 << std::endl; }
    ;

coeff_ket : ket { $$ = $1; }
          | numeric space ket { $$ = $3; std::cout << "coeff_ket: " << $1 << *$3 << std::endl; }
          ;

literal_sequence : coeff_ket { $$ = $1; }
              | TMINUS space coeff_ket { $$ = $3; }
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

parameter : fraction { $$ = new std::string(std::to_string($1)); }
          | simple_op { $$ = $1; }
          | parameter_string { $$ = $1; }
          | TSTAR { $$ = new std::string("*"); }
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

bracket_ops : TLPAREN symbol_op_sequence TRPAREN { $$ = $2; std::cout << "bracket_ops" << std::endl; }
            ;

symbol_op_sequence : space op_sequence space { $$ = $2; }
                   | space op_symbol space op_sequence space { $$ = $4; }
                   | symbol_op_sequence op_symbol space op_sequence space { $$ = $1; }
                   ;

general_op : simple_op { $$ = $1; }
           | compound_op { $$ = $1; }
           | function_op { $$ = $1; }
           | fraction { $$ = new std::string(std::to_string($1)); }
           | bracket_ops { $$ = $1; }
           | TQUOTE TQUOTE { $$ = new std::string(); } // doesn't work for now.
           ;

powered_op : general_op TPOW TINTEGER { $$ = $1; std::cout << "powered_op: " << *$1 << "^" << *$3 << std::endl; }
           ;

op : powered_op { $$ = $1; }
   | general_op { $$ = $1; }
   ;

op_sequence : op { $$ = $1; }
            | op_sequence TSPACE op { $$ = $1; std::cout << "op_sequence: " << *$1 << " " << *$3 << std::endl; }
            ;

comment : space TCOMMENT { std::cout << "TCOMMENT" << std::endl; }
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
    // Open a file handle to a particular file:
    FILE *src = fopen(argv[1], "r");
    // Make sure it is valid:
    if (!src) {
        printf("Can't open file\n");
        return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = src;
  
    // Parse through the input until eof:
    do {
        yyparse();
    } while (!feof(yyin));

    return 0;
}
