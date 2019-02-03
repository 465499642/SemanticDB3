#include <gmpxx.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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
    for (auto token: v) {
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
