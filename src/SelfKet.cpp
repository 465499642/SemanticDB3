#include <string>
#include "SelfKet.h"
#include "Ket.h"
#include "Superposition.h"
#include "Sequence.h"
#include "Functions.h"

const std::string SelfKet::to_string() const {
    std::string coeff = "";
    if ( !double_eq(value, 1.0) ) {
        coeff = std::to_string(value);
    }
    std::string s = "";
    if (idx == 1 ) {
        s = "|_self>";
    } else {
        s = "|_self" + std::to_string(idx) + ">";
    }
    return coeff + s;
}

Ket SelfKet::to_ket() const {
    Ket tmp("_self", value);
    return tmp;
}

Superposition SelfKet::to_sp() const {
    Superposition tmp("_self", value);
    return tmp;
}

Sequence SelfKet::to_seq() const {
    Ket tmp("_self", value);
    Sequence seq(tmp);
    return seq;
}

Sequence SelfKet::Compile(ContextList& context) const {
    return this->to_seq();
}

Sequence SelfKet::Compile(ContextList& context, const ulong label_idx) const {
    if (idx == 1) {
        Ket tmp(label_idx, value);
        return tmp.to_seq();
    }
    return this->to_seq();
}

Sequence SelfKet::Compile(ContextList& context, const std::vector<Sequence>& args) const {
    if (idx < args.size()) {
        return args.at(idx);
    }
    return this->to_seq();
}
