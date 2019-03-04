#include <iostream>
#include "Ket.h"
#include "Sequence.h"
#include "Superposition.h"
#include "Functions.h"
#include "BaseRule.h"


Sequence::Sequence(const std::string& s) {
    Superposition tmp(s);
    seq.push_back(tmp);
}

Sequence::Sequence(const std::string& s, const double d) {
    Superposition tmp(s, d);
    seq.push_back(tmp);
}

Sequence::Sequence(const Ket& k) {
    Superposition tmp;
    tmp.add(k);
    seq.push_back(tmp);
}

Sequence::Sequence(const Superposition& sp) {
    Superposition tmp;
    tmp.add(sp);
    seq.push_back(tmp);
}

Sequence::Sequence(const Sequence& seq2) {
    for (const auto sp: seq2.seq) {
        seq.push_back(sp);
    }
}

Sequence Sequence::operator+(Sequence& b) {
    Sequence tmp;
    tmp.append(*this);
    tmp.append(b);
    return tmp;
}

Superposition Sequence::operator[](const ulong pos) const { // bugs out if pos is out of range.
    // if (pos >= seq.size()) { return Superposition(); }   // fix, is to uncomment this line
    return seq[pos];
}

const ulong Sequence::size() const {
    ulong result;
    result = seq.size();
    return result;
}

void Sequence::add(const Ket& k) {
    if ( seq.size() == 0 ) {
        Superposition tmp;
        tmp.add(k);
        seq.push_back(tmp);
    }
    else {
        seq.back().add(k);
    }
}

void Sequence::add(const Superposition& sp) {
    if ( seq.size() == 0 ) {
        Superposition tmp;
        tmp.add(sp);
        seq.push_back(tmp);
    }
    else {
        seq.back().add(sp);
    }
}

void Sequence::add(const Sequence& seq2) {
    if (seq2.seq.size() == 0 ) { return; }
    if (seq.size() == 0 ) {
        seq = seq2.seq;
    } else {
        Sequence tail(seq2);
        Superposition head = tail.seq.front();
        tail.seq.erase(tail.seq.begin());
        seq.back().add(head);
        this->append(tail);
    }
}

void Sequence::multiply(const double d) {
    for (ulong idx = 0; idx < seq.size(); idx++) {
        seq[idx].multiply(d);
    }
}

void Sequence::append(const Ket& k) {
    Superposition tmp;
    tmp.add(k);
    seq.push_back(tmp);
}

void Sequence::append(const Superposition& sp) {
    Superposition tmp;
    tmp.add(sp);
    seq.push_back(tmp);
}

void Sequence::append(const Sequence& seq2) {
    for (const auto sp: seq2.seq) {
        seq.push_back(sp);
    }
}

const std::string Sequence::to_string() const {
    if (seq.size() == 0) { return std::string("|>"); }
    std::string s;
    bool first_pass = true;
    for (const auto &sp: seq) {
        if (first_pass) {
            s += sp.to_string();
            first_pass = false;
        }
        else {
            s += " . " + sp.to_string();
        }

    }
    return s;
}

Superposition Sequence::get(ulong idx) const {
    if (idx >= seq.size() ) { Superposition tmp; return tmp; }
    return seq[idx];
}

Ket Sequence::to_ket() const {
    if (seq.size() == 0) { Ket tmp; return tmp; }
    Ket tmp = seq[0].to_ket();
    return tmp;
}

Superposition Sequence::to_sp() const {
    if (seq.size() == 0 ) { Superposition tmp; return tmp; }
    Superposition tmp = seq[0];
    return tmp;
}

Sequence Sequence::to_seq() const {
    Sequence tmp(*this);
    return tmp;
}


void Sequence::merge(const Sequence& seq2, const std::string& s) {
    if (seq2.seq.size() == 0 ) { return; }
    if (seq.size() == 0 ) { this->add(seq2); return; }
    Superposition head, tail;
    head = seq.back();
    tail = seq2.seq.front();
    head.merge(tail, s);
    seq.pop_back();
    seq.push_back(head);
    for (ulong i = 1; i < seq2.seq.size(); i++ ) {
        Superposition sp;
        sp = seq2.seq[i];
        seq.push_back(sp);
    }
}

void Sequence::merge(const Sequence& seq2) {
    this->merge(seq2, "");
}


BaseRule* Sequence::b_add(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Sequence *seq = new Sequence(*this); seq->add(brule->to_sp()); return seq; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->add(brule->to_seq()); return seq; }
        default: return this;
    }
}

BaseRule* Sequence::b_append(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Sequence *seq = new Sequence(*this); seq->append(brule->to_sp()); return seq; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->append(brule->to_seq()); return seq; }
        default: return this;
    }
}

Sequence Sequence::Compile(ContextList& context) const {
    return this->to_seq();
}

Sequence Sequence::Compile(ContextList& context, const ulong label_idx) const {
    return this->to_seq();
}

Sequence Sequence::Compile(ContextList& context, const std::vector<Sequence>& args) const {
    return this->to_seq();
}


Sequence Sequence::shuffle() const {
    Sequence result;
    for (const auto sp: seq) {
        Superposition r = sp.shuffle();
        result.seq.push_back(r);
    }
    return result;
}

Sequence Sequence::sreverse() const {
    Sequence result;
    for (auto it = seq.rbegin(); it != seq.rend(); ++it) {
        result.seq.push_back(*it);
    }
    return result;
}

Sequence Sequence::sdrop() const {
    Sequence result;
    for (const auto sp: seq) {
        Superposition r = sp.drop();
        if (r.size() > 0) {
            result.seq.push_back(r);
        }
    }
    return result;
}

Sequence Sequence::apply_sigmoid(std::function<double(double)> sigmoid) const {
    Sequence result;
    for (const auto sp: seq) {
        // Superposition tmp = sp.apply_sigmoid(sigmoid); // not sure which approach is better.
        // result.seq.push_back(tmp);
        result.seq.push_back(sp.apply_sigmoid(sigmoid));
    }
    return result;
}

Sequence Sequence::apply_sigmoid(std::function<double(double,double)> sigmoid, const double t) const {
    Sequence result;
    for (const auto sp: seq) {
        Superposition tmp = sp.apply_sigmoid(sigmoid, t);
        result.seq.push_back(tmp);
    }
    return result;
}

Sequence Sequence::apply_sigmoid(std::function<double(double,double,double)> sigmoid, const double t1, const double t2) const {
    Sequence result;
    for (const auto sp: seq) {
        Superposition tmp = sp.apply_sigmoid(sigmoid, t1, t2);
        result.seq.push_back(tmp);
    }
    return result;
}

Sequence Sequence::apply_ket_fn(std::function<Sequence(const Ket&)> fn) const {
    if (seq.size() == 0 ) {
        Ket k;
        return fn(k);
    }
    Sequence result;
    for (const auto sp: seq) {
        Sequence tmp;
        if (sp.size() == 0 ) {
            Ket k;
            tmp.add(fn(k));
        } else {
            for (const auto k: sp) {
                Sequence tmp2 = fn(k);
                tmp.add(tmp2);
            }
        }
        result.append(tmp);
    }
    return result;
}

Sequence Sequence::apply_sp_fn(std::function<Sequence(const Superposition&)> fn) const {
    Sequence result;
    for (const auto sp: seq) {
        Sequence tmp = fn(sp);
        result.append(tmp);  // not sure if it should be result.add(tmp)
    }
    return result;
}
