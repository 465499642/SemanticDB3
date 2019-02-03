#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Ket.h"
#include "Sequence.h"
#include "ContextList.h"


std::vector<std::string> split(const std::string& s, const std::string& delimiter);
std::string join(const std::vector<std::string>& v, const std::string& delimiter);
bool double_eq(const double v1, const double v2);

Ket extract_head(Ket k);
Ket extract_tail(Ket k);
Ket extract_category(Ket k);
Ket extract_value(Ket k);

// Sequence arithmetic(ContextList &context, std::vector<Sequence> seq_vec);
Sequence arithmetic(ContextList &context, Sequence &input_seq, Sequence &one, Sequence &symbol_ket, Sequence &two);

#endif
