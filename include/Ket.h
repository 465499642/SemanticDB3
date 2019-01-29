#ifndef KET_H
#define KET_H

#define KET 0

#include <string>
#include "KetMap.h"
#include "BaseRule.h"

class Superposition;
class Sequence;

class Ket : public BaseRule {
    private:
        ulong ket_label_idx;
        double ket_value;

    public:
        Ket() {
            ket_label_idx = ket_map.get_idx("");
            ket_value = 1;
        }
        Ket(const ulong idx) {
            ket_label_idx = idx;
            ket_value = 1;
        }
        Ket(const ulong idx, const double v) {
            ket_label_idx = idx;
            ket_value = v;
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
        const ulong size();
        const ulong label_idx();
        std::string label();
        const double value();
        std::string to_string();
        std::vector<ulong> label_split_idx();

        void multiply(const double d);

        Ket to_ket();
        Superposition to_sp();
        Sequence to_seq();

        BaseRule* b_add(BaseRule* brule);
        BaseRule* b_append(BaseRule* brule);

        void merge(Ket k);
        void merge(Ket k, const std::string& s);

        Sequence Compile(ContextList& context);
        Sequence Compile(ContextList& context, const ulong label_idx);
};

#endif
