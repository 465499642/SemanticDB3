#include <iostream>
#include "Sequence.h"
#include "Superposition.h"
#include "Functions.h"

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

Sequence Sequence::operator+(Sequence& b) {
    Sequence tmp;
    tmp.add(*this);
    tmp.add(b);
    return tmp;
}

ulong Sequence::size() {
    ulong result;
    result = seq.size();
    return result;
}

void Sequence::add(Ket& k) {
    Superposition tmp;
    tmp.add(k);
    seq.push_back(tmp);
}

void Sequence::add(Superposition& sp) {
    Superposition tmp;
    tmp.add(sp);
    seq.push_back(tmp);
}

void Sequence::add(Sequence& seq2) {
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
