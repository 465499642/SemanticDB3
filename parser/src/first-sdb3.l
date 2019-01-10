%{
    #include <iostream>
    extern int yylex();
%}
%option noyywrap
%%
\n                                    { std::cout << "Found a new line" << std::endl; }
[ ]+                                  { std::cout << "TSPACE" << std::endl; }
"--".*                                { std::cout << "Found a comment" << std::endl; }
[ ]*"|context> => |context: "         { std::cout << "Found a context learn rule: " << yytext << std::endl; }
[ ]*"supported-ops".*                 { std::cout << "Found a supported-ops learn rule" << std::endl; }
[0-9]+\.[0-9]+                        { std::cout << "Found a float: " << yytext << std::endl; }
[0-9]+                                { std::cout << "Found an integer: " << yytext << std::endl; }
"|"                                   { std::cout << "TPIPE" << std::endl; }
"+=>"                                 { std::cout << "TADD_LEARN_SYM" << std::endl; }
".=>"                                 { std::cout << "TSEQ_LEARN_SYM" << std::endl; }
"#=>"                                 { std::cout << "TSTORE_LEARN_SYM" << std::endl; }
"!=>"                                 { std::cout << "TMEM_LEARN_SYM" << std::endl; }
"=>"                                  { std::cout << "TLEARN_SYM" << std::endl; }
"+"                                   { std::cout << "TPLUS" << std::endl; }
"-"                                   { std::cout << "TMINUS" << std::endl; }
"."                                   { std::cout << "TSEQ" << std::endl; }
"__"                                  { std::cout << "TMERGE2" << std::endl; }
"_"                                   { std::cout << "TMERGE" << std::endl; }
">"                                   { std::cout << "TGT" << std::endl; }
"<"                                   { std::cout << "TLT" << std::endl; }
"("                                   { std::cout << "TLPAREN" << std::endl; }
")"                                   { std::cout << "TRPAREN" << std::endl; }
"["                                   { std::cout << "TLSQUARE" << std::endl; }
"]"                                   { std::cout << "TRSQUARE" << std::endl; }
"/"                                   { std::cout << "TDIVIDE" << std::endl; }
"["[^\[\]<|>]*"]"                     { std::cout << "Found a paramter: " << yytext << std::endl; }
[a-zA-Z!][a-zA-Z0-9\-\+!?\.:]+        { std::cout << "Found an op label: " << yytext << std::endl; }
"|"[^<|>]*">"                         { std::cout << "Found a ket: " << yytext << std::endl; }
.                                     { std::cout << "Found unrecognized object" << std::endl; }
%%

int main(int, char**) {
    // lex through input:
    while (yylex());
}
