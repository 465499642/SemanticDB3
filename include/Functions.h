#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Ket.h"
#include "Sequence.h"
#include "Superposition.h"
#include "ContextList.h"

const double EPSILON = 0.0001;

std::vector<std::string> split(const std::string& s, const std::string& delimiter);
std::string join(const std::vector<std::string>& v, const std::string& delimiter);
bool double_eq(const double v1, const double v2);

Ket extract_head(const Ket k);
Ket extract_tail(const Ket k);
Ket extract_category(const Ket k);
Ket extract_value(const Ket k);

// Sequence arithmetic(ContextList &context, std::vector<Sequence> seq_vec);
Sequence arithmetic(ContextList &context, const Sequence &input_seq, const Sequence &one, const Sequence &symbol_ket, const Sequence &two);
double simm(const Superposition &sp1, const Superposition &sp2);
double scaled_simm(const Superposition &sp1, const Superposition &sp2);
double simm(const Sequence &seq1, const Sequence &seq2);
double scaled_simm(const Sequence &seq1, const Sequence &seq2);

Sequence ket_simm(const Sequence &input_seq, const Sequence &seq1, const Sequence &seq2);
Sequence ket_scaled_simm(const Sequence &input_seq, const Sequence &seq1, const Sequence &seq2);

Superposition sp_intersection(const Superposition &sp1, const Superposition &sp2);
Sequence seq_intersection(const Sequence &input_seq, const Sequence &one, const Sequence &two);

Ket push_float(const Ket &k);
Ket pop_float(const Ket &k);

double normed_frequency_class(const Ket &k, const Superposition &sp);

Superposition split(const Ket &k);
Superposition rank(const Superposition& sp);

Sequence seq_split(const Ket &k);
Sequence seq_rank(const Superposition& sp);

Sequence range(const Sequence &input_seq, const Sequence &start, const Sequence &stop);
Sequence range(const Sequence &input_seq, const Sequence &start, const Sequence &stop, const Sequence &step);

Sequence range2(const Sequence &input_seq, const Sequence &start, const Sequence &stop);
Sequence range3(const Sequence &input_seq, const Sequence &start, const Sequence &stop, const Sequence &step);


Sequence sp2seq(const Superposition &sp);
Superposition seq2sp(const Sequence &seq);

Sequence bar_chart(const Superposition &sp, const double v);
Sequence print_ket(const Ket &k);

#endif
