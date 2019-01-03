#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"

Superposition::Superposition(const ulong idx) {
    sp[idx] = 1.0;
    sort_order.push_back(idx);
}

Superposition::Superposition(const std::string& s) {
    ulong idx = ket_map.get_idx(s);
    sp[idx] = 1.0;
    sort_order.push_back(idx);
}

Superposition::Superposition(const std::string& s, const double v) {
    ulong idx = ket_map.get_idx(s);
    sp[idx] = v;
    sort_order.push_back(idx);
}

Superposition::Superposition(const ulong idx, const double v) {
    sp[idx] = v;
    sort_order.push_back(idx);
}

Superposition Superposition::operator+(Ket& b) {
    Superposition tmp;
    tmp.add(*this);
    tmp.add(b);
    return tmp;
}

/*
Superposition Superposition::operator+(Ket& a, Ket& b) {
    Superposition tmp;
    tmp.add(a);
    tmp.add(b);
    return tmp;
}
*/

//Superposition::operator+(const Superposition& b) {
//    Superposition result;
//    return result;
//}

// bugs out for now:
// void Superposition::add(const Ket& a) {
void Superposition::add(Ket& a) {
    ulong idx = a.label_idx();
    double v = a.value();

    if (this->sp.find(idx) != this->sp.end()) {
        this->sp[idx] += v;
    }
    else {
        this->sp[idx] = v;
        this->sort_order.push_back(idx);
    }
    return;
}

void Superposition::add(Superposition& a) {
    for (ulong idx: a.sort_order) {
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
    std::string label;
    for (auto idx: sort_order) {
        auto label = ket_map.get_str(idx);
        auto value = sp[idx];

        if (idx == sort_order[0]) {
            s += std::to_string(value) + "|" + label + ">";
        }
        else {
            s += " + " + std::to_string(value) + "|" + label + ">";
        }
    }
    return s;
}
