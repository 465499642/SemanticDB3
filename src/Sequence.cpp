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

Sequence::Sequence(Ket& k) {
    Superposition tmp;
    tmp.add(k);
    seq.push_back(tmp);
}

Sequence::Sequence(Superposition& sp) {
    Superposition tmp;
    tmp.add(sp);
    seq.push_back(tmp);
}

Sequence::Sequence(const Sequence& seq2) {
    for (auto sp: seq2.seq) {
        seq.push_back(sp);
    }
}

Sequence Sequence::operator+(Sequence& b) {
    Sequence tmp;
    tmp.append(*this);
    tmp.append(b);
    return tmp;
}

const ulong Sequence::size() {
    ulong result;
    result = seq.size();
    return result;
}

void Sequence::add(Ket& k) {
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

void Sequence::append(Ket& k) {
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
    for (auto sp: seq2.seq) {
        seq.push_back(sp);
    }
}

std::string Sequence::to_string() {
    std::string s;
    bool first_pass = true;
    for (auto sp: seq) {
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

Ket Sequence::to_ket() {
    if (seq.size() == 0) { Ket tmp; return tmp; }
    Ket tmp = seq[0].to_ket();
    return tmp;
}

Superposition Sequence::to_sp() {
    if (seq.size() == 0 ) { Superposition tmp; return tmp; }
    Superposition tmp = seq[0];
    return tmp;
}

Sequence Sequence::to_seq() {
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

Sequence Sequence::Compile(ContextList& context) {
    return this->to_seq();
}
