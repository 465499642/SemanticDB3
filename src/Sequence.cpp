#include <iostream>
#include "Sequence.h"
#include "Superposition.h"
#include "Functions.h"

Sequence::Sequence(Ket& k) {
    Superposition sp;
    sp.add(k);
    seq.push_back(sp);
}

Sequence::Sequence(Superposition& sp) {
    Superposition sp2;
    sp2.add(sp);
    seq.push_back(sp2);
}

Sequence Sequence::add(Ket& k) {
    Superposition sp;
    sp.add(k);
    std::cout << "new sp: " << sp.to_string() << std::endl;
    this->seq.push_back(sp);
    std::cout << "made it here!" << std::endl;
}

Sequence Sequence::add(Superposition& sp) {
    Superposition tmp;
    tmp.add(sp);
    seq.push_back(tmp);
    std::cout << this->to_string() << std::endl;
    std::cout << "made it here too!" << std::endl;
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
