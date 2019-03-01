#include <iostream>
#include "KetMap.h"
#include "FnMap.h"
#include "Functions.h"

FnMap fn_map;

FnMap::FnMap() {
    ulong idx = ket_map.get_idx("range");
    fn_map.whitelist_2.emplace(idx, &range2);
    fn_map.whitelist_3.emplace(idx, &range3);

    idx = ket_map.get_idx("arithmetic");
    fn_map.context_whitelist_3.emplace(idx, &arithmetic); // later remove context dependence of arithmetic.

    idx = ket_map.get_idx("simm");
    fn_map.whitelist_2.emplace(idx, &ket_simm);
}


void FnMap::print() const {
    std::cout << "whitelist_1:" << std::endl;
    for (auto it : whitelist_1) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_2:" << std::endl;
    for (auto it : whitelist_2) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_3:" << std::endl;
    for (auto it : whitelist_3) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_4:" << std::endl;
    for (auto it : whitelist_4) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }

    std::cout << "context_whitelist_1:" << std::endl;
    for (auto it : context_whitelist_1) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_2:" << std::endl;
    for (auto it : context_whitelist_2) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_3:" << std::endl;
    for (auto it : context_whitelist_3) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_4:" << std::endl;
    for (auto it : context_whitelist_4) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
}
