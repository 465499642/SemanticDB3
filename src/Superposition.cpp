#include <math.h>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"
#include "Sequence.h"

Superposition::Superposition(const ulong idx) {
    if (ket_map.get_idx("") == idx) {return; }

    sp[idx] = 1.0;
    sort_order.push_back(idx);
}

Superposition::Superposition(const std::string& s) {
    if (s == "") {return; }

    ulong idx = ket_map.get_idx(s);
    sp[idx] = 1.0;
    sort_order.push_back(idx);
}

Superposition::Superposition(const std::string& s, const double v) {
    if (s == "") {return; }

    ulong idx = ket_map.get_idx(s);
    sp[idx] = v;
    sort_order.push_back(idx);
}

Superposition::Superposition(const ulong idx, const double v) {
    if (ket_map.get_idx("") == idx) {return; }

    sp[idx] = v;
    sort_order.push_back(idx);
}

Superposition Superposition::operator+(Ket& b) {
    Superposition tmp;
    tmp.add(*this);
    tmp.add(b);
    return tmp;
}

ulong Superposition::size() {
    ulong result;
    result = sort_order.size();
    return result;
}

void Superposition::add(const ulong idx) {
    if (ket_map.get_idx("") == idx) {return; }

    if (sp.find(idx) != sp.end()) {
        sp[idx] += 1.0;
    }
    else {
        sp[idx] = 1.0;
        sort_order.push_back(idx);
    }
    return;
}


void Superposition::add(const std::string& s) {
    ulong idx = ket_map.get_idx(s);
    if (ket_map.get_idx("") == idx) {return; }

    if (sp.find(idx) != sp.end()) {
        sp[idx] += 1.0;
    }
    else {
        sp[idx] = 1.0;
        sort_order.push_back(idx);
    }
    return;
}

// const bugs out for now:
// void Superposition::add(const Ket& a) {
void Superposition::add(Ket& a) {
    ulong idx = a.label_idx();
    double v = a.value();

    if (ket_map.get_idx("") == idx) {return; }  // |> is the identity element for superpositions. sp + |> == |> + sp == sp

    if (sp.find(idx) != sp.end()) {
        sp[idx] += v;
    }
    else {
        sp[idx] = v;
        sort_order.push_back(idx);
    }
    return;
}

void Superposition::add(Superposition& a) {
    ulong identity_idx = ket_map.get_idx("");

    for (ulong idx: a.sort_order) {
        if (identity_idx == idx) {continue;}
        if (sp.find(idx) != sp.end()) {
            sp[idx] += a.sp[idx];
        }
        else {
            sp[idx] = a.sp[idx];
            sort_order.push_back(idx);
        }
    }

    return;
}

std::string Superposition::to_string() {
    std::string s;
    if (sp.size() == 0) {s = "|>"; return s; }

    std::string label;
    std::string value_string;
    std::string sign;
    bool first_pass = true;
    for (auto idx: sort_order) {
        auto label = ket_map.get_str(idx);
        auto value = sp[idx];
        sign = " + ";
        if (double_eq(value, 1.0)) {
            value_string = "";
        }
        else {
            value_string = std::to_string(fabs(value));
            if (value < 0) { sign = " - "; }
        }

        if (first_pass && value >= 0) {
            s += value_string + "|" + label + ">";
            first_pass = false;
        }
        else if (first_pass && value < 0) {
            s += "- " + value_string + "|" + label + ">";
            first_pass = false;
        }
        else {
            s += sign + value_string + "|" + label + ">";
        }
    }
    return s;
}

void Superposition::multiply(const double d) {
    for (ulong idx: sort_order) {
        sp[idx] *= d;
    }
}

Ket Superposition::to_ket() {
    if (sp.size() == 0) { Ket tmp; return tmp; }
    ulong op_idx = sort_order[0];
    double value = sp[op_idx];
    Ket tmp(op_idx, value);
    return tmp;
}

Superposition Superposition::to_sp() {
    Superposition tmp(*this);
    return tmp;
}

Sequence Superposition::to_seq() {
    Sequence tmp(*this);
    return tmp;
}


// SuperpositionIter:
Ket Superposition::get(ulong idx) const {
    if (idx >= sort_order.size() ) { Ket tmp; return tmp; }
    ulong sp_idx = sort_order[idx];
    double value = sp.at(sp_idx);
    Ket tmp(sp_idx, value);
    return tmp;
}

SuperpositionIter Superposition::begin () const {
    return SuperpositionIter(this, 0);
}

SuperpositionIter Superposition::end () const {
    return SuperpositionIter(this, this->sort_order.size());
}


Superposition Superposition::merge(const Superposition& sp2, const std::string& s) {
    if (sp2.sort_order.size() == 0 ) { return *this; }
    if (sort_order.size() == 0 ) { return sp2; }
    Superposition tmp;
    for (ulong i = 0; i < sort_order.size() - 1; i++) {
        ulong idx = sort_order[i];
        double value = sp.at(idx);
        tmp.sp[idx] = value;
        tmp.sort_order.push_back(idx);
    }
    ulong head_idx = sort_order.back();
    ulong tail_idx = sp2.sort_order.front();
    std::string s2 = ket_map.get_str(head_idx) + s + ket_map.get_str(tail_idx);
    ulong new_idx = ket_map.get_idx(s2);
    double head_value = sp.at(head_idx);
    double tail_value = sp2.sp.at(tail_idx);
    tmp.sp[new_idx] = head_value * tail_value;
    tmp.sort_order.push_back(new_idx);
    for (ulong i = 1; i < sp2.sort_order.size(); i++) {
        ulong idx = sp2.sort_order[i];
        double value = sp2.sp.at(idx);
        tmp.sp[idx] = value;
        tmp.sort_order.push_back(idx);
    }
    return tmp;
}

Superposition Superposition::merge(const Superposition& sp2) {
    return this->merge(sp2, "");
}

