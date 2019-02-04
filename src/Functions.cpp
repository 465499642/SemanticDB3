#include <gmpxx.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include "Functions.h"
#include "KetMap.h"
#include "Ket.h"

const double EPSILON = 0.0001; // shift to Functions.h?


// from here:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(s.substr(pos_start));
    return result;
}

std::string join(const std::vector<std::string>& v, const std::string& delimiter) {
    std::string s;
    bool first_pass = true;
    for (const auto &token: v) {
        if (first_pass) {
            s += token;
            first_pass = false;
        }
        else {
            s += delimiter + token;
        }
    }
    return s;
}

bool double_eq(const double v1, const double v2) {
    if (fabs(v1 - v2) < EPSILON ) {
        return true;
    }
    return false;
}



Ket extract_head(Ket k) {
    ulong head_idx = ket_map.get_head_idx(k.label_idx());
    Ket result(head_idx, k.value());
    return result;
}

Ket extract_tail(Ket k) {
    ulong tail_idx = ket_map.get_tail_idx(k.label_idx());
    Ket result(tail_idx, k.value());
    return result;
}

Ket extract_category(Ket k) {
    ulong category_idx = ket_map.get_category_idx(k.label_idx());
    Ket result(category_idx, k.value());
    return result;
}

Ket extract_value(Ket k) {
    ulong value_idx = ket_map.get_value_idx(k.label_idx());
    Ket result(value_idx, k.value());
    return result;
}


Sequence arithmetic(ContextList &context, Sequence &input_seq, Sequence &one, Sequence &symbol_ket, Sequence &two) {
    auto one_idx_vec = one.to_ket().label_split_idx();
    auto symbol = symbol_ket.to_ket().label();
    auto two_idx_vec = two.to_ket().label_split_idx();

    if (one_idx_vec.size() == 0 || two_idx_vec.size() == 0 || symbol.size() == 0) { Sequence tmp; return tmp; }
    auto one_str = ket_map.get_str(one_idx_vec.back());
    auto two_str = ket_map.get_str(two_idx_vec.back());
    one_idx_vec.pop_back();
    two_idx_vec.pop_back();

    if (one_idx_vec != two_idx_vec) { Sequence tmp; return tmp; }

    // mpz_class x(one_str), y(two_str), value;
    mpf_class x(one_str), y(two_str), value;

    char symbol_char = symbol.front();
    switch(symbol_char) {
        case '+' : { value = x + y; break; }
        case '-' : { value = x - y; break; }
        case '*' : { value = x * y; break; }
        case '/' : { value = x / y; break; }
        // case '%' : { value = x % y; break; }
    }
    std::stringstream buffer;
    buffer.precision(10);
    buffer << value;
    Sequence result(buffer.str());
    // Sequence result(value.get_str(10));
    // Sequence result(std::to_string(value));
    return result;
}


double simm(const Superposition &sp1, const Superposition &sp2) {
    if (sp1.size() == 0 || sp2.size() == 0) { return 0; }
    std::set<ulong> merged;
    std::unordered_map<ulong, double> one, two;
    double one_sum(0), two_sum(0), merged_sum(0);
    for (const auto k : sp1) {
        one[k.label_idx()] = k.value();
        merged.insert(k.label_idx());
        one_sum += k.value();
    }
    for (const auto k : sp2) {
        two[k.label_idx()] = k.value();
        merged.insert(k.label_idx());
        two_sum += k.value();
    }

    if ( double_eq(one_sum, 0) || double_eq(two_sum, 0)) { return 0; } // prevent div by zero

    for (const auto idx : merged) {
        if (one.find(idx) != one.end() && two.find(idx) != two.end()) {
            double v1 = one[idx];
            double v2 = two[idx];
            merged_sum += std::min(v1, v2);
        }
    }
    return merged_sum / std::max(one_sum, two_sum);
}

double scaled_simm(const Superposition &sp1, const Superposition &sp2) {
    if (sp1.size() == 0 || sp2.size() == 0) { return 0; }

    if (sp1.size() == 1 && sp2.size() == 1) {
        Ket k1 = sp1.to_ket();
        Ket k2 = sp2.to_ket();
        if (k1.label_idx() != k2.label_idx()) { return 0; }
        double a = std::max(k1.value(), 0.0);
        double b = std::max(k2.value(), 0.0);
        if ( double_eq(a, 0) && double_eq(b, 0)) { return 0; }
        return std::min(a, b) / std::max(a, b);
    }

    std::set<ulong> merged;
    std::unordered_map<ulong, double> one, two;
    double one_sum(0), two_sum(0), merged_sum(0);
    for (const auto k : sp1) {
        one[k.label_idx()] = k.value();
        merged.insert(k.label_idx());
        one_sum += k.value();
    }
    for (const auto k : sp2) {
        two[k.label_idx()] = k.value();
        merged.insert(k.label_idx());
        two_sum += k.value();
    }

    if ( double_eq(one_sum, 0) || double_eq(two_sum, 0)) { return 0; } // prevent div by zero

    for (const auto idx : merged) {
        if (one.find(idx) != one.end() && two.find(idx) != two.end()) {
            double v1 = one[idx] / one_sum;
            double v2 = two[idx] / two_sum;
            merged_sum += std::min(v1, v2);
        }
    }
    return merged_sum;
}

double simm(const Sequence &seq1, const Sequence &seq2) {
    ulong size = std::min(seq1.size(), seq2.size());
    if (size == 0) { return 0; }
    double r = 0;
    for (ulong k = 0; k < size; k++) {
        r += simm(seq1.get(k), seq2.get(k));
    }
    return r / size;
}

double scaled_simm(const Sequence &seq1, const Sequence &seq2) {
    ulong size = std::min(seq1.size(), seq2.size());
    if (size == 0) { return 0; }
    double r = 0;
    for (ulong k = 0; k < size; k++) {
        r += scaled_simm(seq1.get(k), seq2.get(k));
    }
    return r / size;
}


