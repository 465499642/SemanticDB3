#include <math.h>
#include "Ket.h"
#include "Superposition.h"

double EPSILON = 0.0001;


Superposition Ket::operator+(Ket& a) {
    Superposition tmp;
    tmp.add(*this);
    tmp.add(a);
    return tmp;
}


ulong Ket::label_idx() {
    return ket_label_idx;
}

std::string Ket::label() {
    std::string result = ket_map.get_str(ket_label_idx);
    return result;
}

double Ket::value() {
    return ket_value;
}

std::string Ket::to_string() {
    std::string s;
    if ( fabs(ket_value - 1.0) < EPSILON ) {
        s = "|" + ket_map.get_str(ket_label_idx) + ">";
    }
    else {
        s = std::to_string(ket_value) + "|" + ket_map.get_str(ket_label_idx) + ">";
    }
    return s;
}

std::vector<ulong> Ket::label_split_idx() {
    std::vector<ulong> result = ket_map.get_split_idx(ket_label_idx);
    return result;
}
