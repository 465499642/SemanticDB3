#include <math.h>
#include <algorithm>
#include <random>
#include <assert.h>
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

Superposition::Superposition(const Superposition &sp1) {
    for (const auto idx : sp1.sort_order) {
       double value = sp1.sp.at(idx);
       sp[idx] = value;
       sort_order.push_back(idx);
    }
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

double Superposition::find_max_coeff() const { // what happens if sp is empty?
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

Ket Superposition::do_you_know() const {
    if (sort_order.size() == 0) { return Ket("no"); }
    return Ket("yes");
}

Ket Superposition::how_many() const {
    ulong count = sort_order.size();
    Ket result("number: " + std::to_string(count));
    return result;
}

Ket Superposition::measure_currency() const {
    double sum = 0;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        sum += value;
    }
    return Ket("number: " + std::to_string(sum)); // use mpf here instead?
}

Ket Superposition::pick_elt() const {
    std::random_device rd;  // is this correct to re-seed on every invoke?
    std::mt19937 eng(rd()); // code from here: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::uniform_int_distribution<> distr(0, sort_order.size() - 1);
    ulong pos = distr(eng);
    ulong idx = sort_order[pos];
    double value = sp.at(idx);
    Ket result(idx, value);
    return result;
}

Ket Superposition::weighted_pick_elt() const {
    Superposition sp1 = this->drop();
    if (sp1.size() == 0) { return Ket(); }
    double sum = 0;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        sum += value;
    }  // sum should be > 0
    std::random_device rd;  // is this correct to re-seed on every invoke?
    std::mt19937 eng(rd()); // code from here: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::uniform_int_distribution<> distr(0, sum);
    ulong r = distr(eng);
    double upto = 0;
    for (const auto k : sp1 ) { // maybe iterate using sort_order instead as an optimization?
        double w = k.value();
        if (upto + w > r) { return k; }
        upto += w;
    }
    assert(false); // we shouldn't get here if everything is working correctly
}

Superposition Superposition::reverse() const {
    Superposition result;
    for ( auto it = sort_order.rbegin(); it != sort_order.rend(); ++it) {
        double value = sp.at(*it);
        result.sp[*it] = value;
        result.sort_order.push_back(*it);
    }
    return result;
}

Superposition Superposition::normalize() const {
    return this->normalize(1);
}

Superposition Superposition::normalize(const double t) const {
    double sum = 0;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        sum += value;
    }
    if (sum == 0) { return *this; }
    Superposition result;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        result.sp[idx] = t * value / sum;
        result.sort_order.push_back(idx);
    }
    return result;
}

Superposition Superposition::rescale() const {
    return this->rescale(1);
}

Superposition Superposition::rescale(const double t) const {
    double the_max = this->find_max_coeff();
    if (the_max == 0) { return *this; }
    Superposition result;
    for (const auto idx : sort_order) {
        double value = sp.at(idx);
        result.sp[idx] = t * value / the_max;
        result.sort_order.push_back(idx);
    }
    return result;
}

Superposition Superposition::shuffle() const {
    Superposition result(*this);

    std::random_device rd; // code from here: https://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::mt19937 g(rd());
    std::shuffle(result.sort_order.begin(), result.sort_order.end(), g);

    return result;
}

/*
bool compare_coeff(const SuperpositionIter &a, const SuperpositionIter &b) {
    return (*a).value() < (*b).value();
}

Superposition Superposition::coeff_sort() const {
    Superposition result(*this);
//    std::sort(result.begin(), result.end(), compare_coeff);
    return result;
}
*/

struct CompareCoeffStruct {
    CompareCoeffStruct(std::unordered_map<ulong, double> *sp) { this->sp = sp; }
//    bool operator () (ulong a, ulong b) { return sp->at(a) < sp->at(b); }
    bool operator () (ulong a, ulong b) { return sp->at(a) > sp->at(b); }
    std::unordered_map<ulong, double> *sp;
};

Superposition Superposition::coeff_sort() const {
    Superposition result(*this);
    std::sort(result.sort_order.begin(), result.sort_order.end(), CompareCoeffStruct(&result.sp));
    return result;
}

bool compare_ket(const ulong a, const ulong b) {
    return ket_map.get_str(a) < ket_map.get_str(b);
}

Superposition Superposition::ket_sort() const {
    Superposition result(*this);
    std::sort(result.sort_order.begin(), result.sort_order.end(), compare_ket);
    return result;
}

Superposition Superposition::select_range(const ulong a, const ulong b) const {
    ulong a1 = std::max((ulong)1, a) - 1;
    ulong b1 = std::min(b, sort_order.size());
    Superposition result;
    for (ulong i = a1; i < b1; i++) {
        ulong idx = sort_order[i];
        double value = sp.at(idx);
        result.add(idx, value);
    }
    return result;
}
