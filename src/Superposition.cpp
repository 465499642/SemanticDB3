#include <math.h>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"

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
    result = sp.size();
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
