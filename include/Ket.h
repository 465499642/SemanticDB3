#ifndef KET_H
#define KET_H

#define KET 0

#include <string>
#include "KetMap.h"
#include "BaseRule.h"

class Superposition;

class Ket : public BaseRule {
    private:
        ulong ket_label_idx;
        double ket_value;

    public:
        Ket() {
            ket_label_idx = ket_map.get_idx("");
            ket_value = 1;
        }
        Ket(const std::string& s) {
            ket_label_idx = ket_map.get_idx(s);
            ket_value = 1;
        }
        Ket(const std::string& s, const double v) {
            ket_label_idx = ket_map.get_idx(s);
            ket_value = v;
        }
        int type() { return KET; };
        Superposition operator+(Ket& a);
        ulong size();
        ulong label_idx();
        std::string label();
        double value();
        std::string to_string();
        std::vector<ulong> label_split_idx();
};

#endif
