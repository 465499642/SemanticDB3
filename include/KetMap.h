#ifndef KETMAP_H
#define KETMAP_H

typedef unsigned long ulong;
#include <unordered_map>
#include <string>
#include <vector>

class KetMap {
    private:
        ulong map_count;
        std::unordered_map<std::string, ulong> our_map;
        std::vector<std::string> our_inverse_map;
        std::unordered_map<std::string, std::vector<ulong> > our_split_map;

    public:
        KetMap();
        ulong get_idx(const std::string& s);
        std::string get_str(const ulong idx);
        std::vector<ulong> get_split_idx(const std::string& s);
        std::vector<ulong> get_split_idx(const ulong idx);
        void print();

        ulong get_head_idx(const ulong idx);
//        ulong get_tail_idx(const ulong idx);
//        ulong get_category_idx(const ulong idx);
        ulong get_value_idx(const ulong idx);
};

extern KetMap ket_map;

#endif

