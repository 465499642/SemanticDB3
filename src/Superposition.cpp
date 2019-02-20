#include <math.h>
#include <algorithm>
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

Superposition::Superposition(Ket k) {
    ulong idx = k.label_idx();
    if (ket_map.get_idx("") == idx) {return; }

    sp[idx] = k.value();
    sort_order.push_back(idx);
}


Superposition Superposition::operator+(Ket& b) {
    Superposition tmp;
    tmp.add(*this);
    tmp.add(b);
    return tmp;
}

const ulong Superposition::size() const {
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

void Superposition::add(const ulong idx, const double v) {
    if (ket_map.get_idx("") == idx) {return; }

    if (sp.find(idx) != sp.end()) {
        sp[idx] += v;
    }
    else {
        sp[idx] = v;
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

void Superposition::add(const Superposition& a) {
    ulong identity_idx = ket_map.get_idx("");

    for (ulong idx: a.sort_order) {
        if (identity_idx == idx) {continue;}
        if (sp.find(idx) != sp.end()) {
            sp[idx] += a.sp.at(idx);
        }
        else {
            sp[idx] = a.sp.at(idx);
            sort_order.push_back(idx);
        }
    }

    return;
}

const std::string Superposition::to_string() const {
    std::string s;
    if (sp.size() == 0) {s = "|>"; return s; }

    std::string label;
    std::string value_string;
    std::string sign;
    bool first_pass = true;
    for (const auto idx: sort_order) {
        auto label = ket_map.get_str(idx);
        auto value = sp.at(idx);
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

Ket Superposition::to_ket() const {
    if (sp.size() == 0) { Ket tmp; return tmp; }
    ulong op_idx = sort_order[0];
    double value = sp.at(op_idx);
    Ket tmp(op_idx, value);
    return tmp;
}

Superposition Superposition::to_sp() const {
    Superposition tmp(*this);
    return tmp;
}

Sequence Superposition::to_seq() const {
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


void Superposition::merge(const Superposition& sp2, const std::string& s) {
    if (sp2.sort_order.size() == 0 ) { return; }
    if (sort_order.size() == 0 ) { this->add(sp2); return; }
    ulong head_idx = sort_order.back();
    double head_value = sp[head_idx];
    sp.erase(head_idx);
    sort_order.pop_back();
    ulong tail_idx = sp2.sort_order.front();
    double tail_value = sp2.sp.at(tail_idx); // does this work: sp2.sp[tail_idx] ?
    std::string s2 = ket_map.get_str(head_idx) + s + ket_map.get_str(tail_idx);
    ulong new_idx = ket_map.get_idx(s2);
    double new_value = head_value * tail_value;
    this->add(new_idx, new_value);
    for (ulong i = 1; i < sp2.sort_order.size(); i++) {
        ulong idx = sp2.sort_order[i];
        double value = sp2.sp.at(idx);
        this->add(idx, value);
    }
}

void Superposition::merge(const Superposition& sp2) {
    this->merge(sp2, "");
}


BaseRule* Superposition::b_add(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Superposition *sp = new Superposition(*this); sp->add(brule->to_sp()); return sp; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->add(brule->to_seq()); return seq; }
        default: return this;
    }
}

BaseRule* Superposition::b_append(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Sequence *seq = new Sequence(*this); seq->append(brule->to_sp()); return seq; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->append(brule->to_seq()); return seq; }
        default: return this;
    }
}


Sequence Superposition::Compile(ContextList& context) const {
    return this->to_seq();
}

Sequence Superposition::Compile(ContextList& context, const ulong label_idx) const {
    return this->to_seq();
}

Sequence Superposition::Compile(ContextList& context, const std::vector<Sequence>& args) const {
    return this->to_seq();
}

bool compare(const std::pair<ulong, double>&a, const std::pair<ulong, double>&b) {
    return a.second < b.second;
}

double Superposition::find_min_coeff() const {
    double smallest = std::min_element(sp.begin(), sp.end(), compare)->second;
    return smallest;
}

double Superposition::find_max_coeff() const {
    double largest = std::max_element(sp.begin(), sp.end(), compare)->second;
    return largest;
}


double Superposition::find_value(const Ket &k) const {
    ulong idx = k.label_idx();
    if (sp.find(idx) == sp.end()) { return 0; }
    return sp.at(idx);
}

Superposition Superposition::drop() const {
    Superposition result;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        if (value > 0) {
            result.sp[idx] = value;
            result.sort_order.push_back(idx);
        }
    }
    return result;
}

Superposition Superposition::drop_below(const double t) const {
    Superposition result;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        if (value >= t) {
            result.sp[idx] = value;
            result.sort_order.push_back(idx);
        }
    }
    return result;
}

Superposition Superposition::drop_above(const double t) const {
    Superposition result;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        if (value <= t) {
            result.sp[idx] = value;
            result.sort_order.push_back(idx);
        }
    }
    return result;
}

