#ifndef KET_H
#define KET_H

#define KET 0

#include <string>
#include <vector>
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
        const int type() const { return KET; };
        Superposition operator+(Ket& a);
        const ulong size() const;
        const ulong label_idx() const;
        const std::string label() const;
        const double value() const;
        const std::string to_string() const;
        const std::vector<ulong> label_split_idx() const;

        void multiply(const double d);

        Ket to_ket() const;
        Superposition to_sp() const;
        Sequence to_seq() const;

        BaseRule* b_add(BaseRule* brule);
        BaseRule* b_append(BaseRule* brule);

        void merge(Ket k);
        void merge(Ket k, const std::string& s);

        Sequence Compile(ContextList& context) const;
        Sequence Compile(ContextList& context, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const;
};

#endif
