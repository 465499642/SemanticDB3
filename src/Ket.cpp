#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"
#include "Sequence.h"
#include "BaseRule.h"


Superposition Ket::operator+(Ket& a) {
    Superposition tmp;
    tmp.add(*this);
    tmp.add(a);
    return tmp;
}


const ulong Ket::label_idx() const {
    return ket_label_idx;
}

const std::string Ket::label() const {
    std::string result = ket_map.get_str(ket_label_idx);
    return result;
}

const double Ket::value() const {
    return ket_value;
}

const ulong Ket::size() const {
    ulong result;
    if (ket_map.get_idx("") == ket_label_idx) {
        result = 0;
    }
    else {
        result = 1;
    }
    return result;
}

const std::string Ket::to_string() const {
    std::string s;
    if ( double_eq(ket_value, 1.0) ) {
        s = "|" + ket_map.get_str(ket_label_idx) + ">";
    } else if ( double_eq(ket_value, -1.0) ) {
        s = "- |" + ket_map.get_str(ket_label_idx) + ">";
    }
    else {
        s = std::to_string(ket_value) + "|" + ket_map.get_str(ket_label_idx) + ">";
    }
    return s;
}


const std::vector<ulong> Ket::label_split_idx() const {
    return ket_map.get_split_idx(ket_label_idx);
}

void Ket::multiply(const double d) {
    ket_value *= d;
}

Ket Ket::to_ket() const {
    Ket tmp(*this);
    return tmp;
}

Superposition Ket::to_sp() const {
    Superposition tmp(this->label_idx(), this->value());
    return tmp;
}

Sequence Ket::to_seq() const {
    Sequence tmp(*this);
    return tmp;
}

BaseRule* Ket::b_add(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Superposition *sp = new Superposition(*this); sp->add(brule->to_sp()); return sp; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->add(brule->to_seq()); return seq; }
        default: return this;
    }
}

BaseRule* Ket::b_append(BaseRule* brule) {
    switch(brule->type()) {
        case KET:
        case SUPERPOSITION: { Sequence *seq = new Sequence(*this); seq->append(brule->to_sp()); return seq; }
        case SEQUENCE: { Sequence *seq = new Sequence(*this); seq->append(brule->to_seq()); return seq; }
        default: return this;
    }
}


void Ket::merge(Ket k) {
    ket_value *= k.ket_value;
    std::string s = this->label() + k.label();
    ket_label_idx = ket_map.get_idx(s);
}

void Ket::merge(Ket k, const std::string& s) {
    ket_value *= k.ket_value;
    std::string s2 = this->label() + s + k.label();
    ket_label_idx = ket_map.get_idx(s2);
}


Sequence Ket::Compile(ContextList& context) const {
    return this->to_seq();
}

Sequence Ket::Compile(ContextList& context, const ulong label_idx) const {
    return this->to_seq();
}

Sequence Ket::Compile(ContextList& context, const std::vector<Sequence>& args) const {
    return this->to_seq();
}
