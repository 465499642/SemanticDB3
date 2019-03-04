#include <gmpxx.h>
#include <math.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
#include "Functions.h"
#include "KetMap.h"
#include "Ket.h"


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


Sequence arithmetic(ContextList &context, const Sequence &input_seq, const Sequence &one, const Sequence &symbol_ket, const Sequence &two) {
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


/*
double simm(const Superposition &sp1, const Superposition &sp2) {
    if (sp1.size() == 0 || sp2.size() == 0) { return 0; }
    std::set<ulong> merged;
    std::unordered_map<ulong, double> one, two;  // wait, do we need one, two? Can't we just use sp1 and sp2?
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
*/

double simm(const Superposition &sp1, const Superposition &sp2) {
    if (sp1.size() == 0 || sp2.size() == 0) { return 0; }
    std::set<ulong> merged;
    double one_sum(0), two_sum(0), merged_sum(0);
    for (const auto k : sp1) {
        merged.insert(k.label_idx());
        one_sum += k.value();
    }
    for (const auto k : sp2) {
        merged.insert(k.label_idx());
        two_sum += k.value();
    }

    if ( double_eq(one_sum, 0) || double_eq(two_sum, 0)) { return 0; } // prevent div by zero

    for (const auto idx : merged) {
        double v1 = sp1.find_value(idx);
        double v2 = sp2.find_value(idx);
        merged_sum += std::min(v1, v2);
    }
    return merged_sum / std::max(one_sum, two_sum);
}

/*
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
*/

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
    double one_sum(0), two_sum(0), merged_sum(0);
    for (const auto k : sp1) {
        merged.insert(k.label_idx());
        one_sum += k.value();
    }
    for (const auto k : sp2) {
        merged.insert(k.label_idx());
        two_sum += k.value();
    }

    if ( double_eq(one_sum, 0) || double_eq(two_sum, 0)) { return 0; } // prevent div by zero

    for (const auto idx : merged) {
        double v1 = sp1.find_value(idx) / one_sum;
        double v2 = sp2.find_value(idx) / two_sum;
        merged_sum += std::min(v1, v2);
    }
    return merged_sum;
}


double simm(const Sequence &seq1, const Sequence &seq2) {
    ulong size = std::min(seq1.size(), seq2.size());
    if (size == 0) { return 0; }
    double r = 0;
    for (ulong k = 0; k < size; k++) {
        r += simm(seq1[k], seq2[k]);
    }
    return r / size;
}

double scaled_simm(const Sequence &seq1, const Sequence &seq2) {
    ulong size = std::min(seq1.size(), seq2.size());
    if (size == 0) { return 0; }
    double r = 0;
    for (ulong k = 0; k < size; k++) {
        r += scaled_simm(seq1[k], seq2[k]);
    }
    return r / size;
}

Sequence ket_simm(const Sequence &input_seq, const Sequence &seq1, const Sequence &seq2) {
    double value = simm(seq1, seq2);
    return Sequence("simm", value);
}

Sequence ket_scaled_simm(const Sequence &input_seq, const Sequence &seq1, const Sequence &seq2) {
    double value = scaled_simm(seq1, seq2);
    return Sequence("simm", value);
}


Superposition sp_intersection(const Superposition &sp1, const Superposition &sp2) {
    if (sp1.size() == 0 || sp2.size() == 0) { return Superposition(); }
    std::set<ulong> merged;
    for (const auto k : sp1) {
        merged.insert(k.label_idx());
    }
    for (const auto k : sp2) {
        merged.insert(k.label_idx());
    }
    Superposition result;
    for (const auto idx: merged) {
        double v1 = sp1.find_value(idx);
        double v2 = sp2.find_value(idx);
        double value = std::min(v1, v2);
        if (value > 0) {
            result.add(idx, value);
        }
    }
    return result;
}

Sequence seq_intersection(const Sequence &input_seq, const Sequence &one, const Sequence &two) {
    ulong min_size = std::min(one.size(), two.size());
    ulong max_size = std::max(one.size(), two.size());
    Sequence result;
    for (ulong i = 0; i < min_size; i++) {
        Superposition r = sp_intersection(one[i], two[i]);
        result.append(r);
    }  // finish! need to append |> . |> etc.
    return result;
}

Ket push_float(const Ket &k) {  // optimize later!
    std::string label = k.label();
    if (label == "") { return k; }
    std::string s;
    if (label == " ") {
        s = "";
    } else {
        s = label + ": ";
    }
    // s += std::to_string(k.value());
    // Ket result(s);
    mpf_class value(k.value());
    std::stringstream buffer;
    buffer.precision(10);
    buffer << value;
    Ket result(s + buffer.str());
    return result;
}

Ket pop_float(const Ket &k) { // optimize later!
    auto k_vec = k.label_split_idx();
    if (k_vec.size() == 0) { Ket result; return result; } // should never happen
    std::string value_str = ket_map.get_str(k_vec.back());
    try {
        //double value = std::stod(value_str);
        mpf_class mpf_value(value_str);
        double value = mpf_value.get_d();
        if ( k_vec.size() == 1 ) {
            Ket result(" ", value);
            return result;
        }
        k_vec.pop_back();
        ulong label_idx = ket_map.get_idx(k_vec);
        Ket result(label_idx, value * k.value());
        return result;
    } catch (std::invalid_argument) {
        return k;
    }
}



double normed_frequency_class(const Ket &k, const Superposition &sp) {
    double smallest = sp.find_min_coeff();
    double largest = sp.find_max_coeff();
    double f = sp.find_value(k);

    if (largest <= 0 or f <= 0) { return 0; }

    double fc_max = floor(0.5 - std::log(smallest / largest)/std::log(2)) + 1;
    return 1 - floor(0.5 - std::log(f / largest)/std::log(2)) / fc_max;
}


// std::vector<std::string> split(const std::string& s, const std::string& delimiter)
Superposition split(const Ket &k) {
    Superposition result;
    auto split_str = split(k.label(), " ");
    double value = k.value();
    for (auto s : split_str) {
        ulong idx = ket_map.get_idx(s);
        result.add(idx, value);
    }
    return result;
}

Superposition rank(const Superposition& sp) {
    Superposition result;
    for (ulong i = 0; i < sp.size(); i++) {
       Ket k = sp.get(i);
       result.add(k.label_idx(), i+1);
    }
    return result;
}

Sequence seq_split(const Ket &k) { // tidy later!
    return Sequence(split(k));
}

Sequence seq_rank(const Superposition& sp) {
    return Sequence(rank(sp));
}

Sequence range2(const Sequence &input_seq, const Sequence &start, const Sequence &stop) {
    return range(input_seq, start, stop);
}

Sequence range3(const Sequence &input_seq, const Sequence &start, const Sequence &stop, const Sequence &step) {
    return range(input_seq, start, stop, step);
}

Sequence range(const Sequence &input_seq, const Sequence &start, const Sequence &stop) {
    Sequence step("1");
    return range(input_seq, start, stop, step);
}

Sequence range(const Sequence &input_seq, const Sequence &start, const Sequence &stop, const Sequence &step) {
    auto start_vec = start.to_ket().label_split_idx();
    auto stop_vec = stop.to_ket().label_split_idx();
    auto step_ket = step.to_ket();
    auto v3 = step_ket.label();
    double direction = step_ket.value();

    if (start_vec.size() == 0 || stop_vec.size() == 0) { return Sequence(); }
    ulong start_idx = start_vec.back();
    ulong stop_idx = stop_vec.back();
    start_vec.pop_back();
    stop_vec.pop_back();
    if ( start_vec != stop_vec ) { return Sequence(); }
    std::string v1 = ket_map.get_str(start_idx);
    std::string v2 = ket_map.get_str(stop_idx);
    std::string cat = ket_map.get_str(start_vec);  // what if start_vec.size() == 0?
    std::string label = "";
    if (cat.size() > 0 ) { label = cat + ": "; }
    Superposition result;
    mpf_class x(v1), y(v2), z(v3), i;
    if (z == 0) { return start; }
    if (direction > 0 ) {
        for (i = x; i <= y; i += z) {
            std::stringstream buffer;
            buffer.precision(10);
            buffer << i;
            result.add(label + buffer.str());
        }
    } else if (direction < 0) {
        for (i = x; i >= y; i -= z) {
            std::stringstream buffer;
            buffer.precision(10);
            buffer << i;
            result.add(label + buffer.str());
        }
    }
    return result.to_seq();
}

Sequence sp2seq(const Superposition &sp) {
    Sequence result;
    for (const auto k : sp) {
        result.append(k);
    }
    return result;
}

Superposition seq2sp(const Sequence &seq) {
    Superposition result;
    for (const auto sp: seq) {
        result.add(sp);
    }
    return result;
}


Sequence bar_chart(const Superposition &sp, const double v) {
    if (sp.size() == 0 || v <= 0) { return Sequence(); }
    ulong width = (ulong)v;
    ulong max_len = 0;
    for (const auto k: sp) {
        max_len = std::max(k.label().size(), max_len);
    }
    // Superposition one = sp.rescale(width); // do we need .drop() too? Probably.
    Superposition one = sp.drop().rescale(width);
    std::cout << "----------" << std::endl;
    for (const auto k: one) {
        std::cout << std::left << std::setfill(' ') << std::setw(max_len) << k.label() << " : ";
        std::cout << std::setfill('|') << std::setw((ulong)k.value()) << "|" << std::endl;
    }
    std::cout << "----------" << std::endl;
    return Sequence("bar chart");
}

Sequence print_ket(const Ket &k) {
    std::cout << k.label() << std::endl;
    return Sequence(k);
}
