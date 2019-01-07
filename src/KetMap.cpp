#include <iostream>
#include "KetMap.h"
#include "Functions.h"

KetMap::KetMap() {
    std::string s = "";
    our_map[s] = 0;
    our_inverse_map.push_back(s);
    map_count = 1;
}

ulong KetMap::get_idx(const std::string& s) {
    ulong result;
    std::vector<ulong> split_result;

    if (our_map.find(s) != our_map.end()) {
        result = our_map[s];
    }
    else {
        our_map[s] = map_count;
        result = map_count;
        map_count++;
        our_inverse_map.push_back(s);

        auto svec = split(s, ": ");
        for (const auto token: svec) {
            if (our_map.find(token) != our_map.end()) {
                split_result.push_back(our_map[token]);
            }
            else {
                our_map[token] = map_count;
                split_result.push_back(map_count);
                map_count++;
                our_inverse_map.push_back(token);
            }
        }
        if (split_result.size() > 1) {
            our_split_map[s] = split_result;
        }
    }
    return result;
}

std::string KetMap::get_str(const ulong idx) {  // what should we return if idx is not in our_inverse_map?
    std::string result;
    if (idx < our_inverse_map.size()) {
        result = our_inverse_map[idx];
    }
    return result;
}

std::vector<ulong> KetMap::get_split_idx(const std::string& s) {
    std::vector<ulong> result;
    ulong r;
    if (our_split_map.find(s) != our_split_map.end()) {
        result = our_split_map[s];
    }
    else {
        if (our_map.find(s) == our_map.end()) {
            r = KetMap::get_idx(s);
        }
        if (our_split_map.find(s) != our_split_map.end()) {
            result = our_split_map[s];
        }
        else {
            result.push_back(our_map[s]);
        }
    }
    return result;
}

std::vector<ulong> KetMap::get_split_idx(const ulong idx) {
    auto s = get_str(idx);
    auto result = get_split_idx(s);
    return result;
}

ulong KetMap::get_head_idx(const ulong idx) {
    ulong result = 0;
    std::vector<ulong> uvect = get_split_idx(idx);
    if (uvect.size() == 0) { return result; };
    result = uvect[0];
    return result;
}

//        ulong get_tail_idx(const ulong idx);
//        ulong get_category_idx(const ulong idx);

ulong KetMap::get_value_idx(const ulong idx) {
    ulong result = 0;
    std::vector<ulong> uvect = get_split_idx(idx);
    if (uvect.size() == 0) { return result; };
    result = uvect.back();
    return result;
}

void KetMap::print() {
    std::cout << "map_count: " << map_count << std::endl;
    std::cout << "our_map:" << std::endl;
    for (auto x: our_map) {
        std::cout << "    " << x.first << " " << x.second << std::endl;
    }
    std::cout << "our_inverse_map:" << std::endl;
    for (auto x: our_inverse_map) {
        std::cout << "    " << x << std::endl;
    }
    std::cout << "our_split_map:" << std::endl;
    for (auto x: our_split_map) {
        std::cout << "    " << x.first << "    ";
        for (auto y: x.second) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
}


KetMap ket_map;
