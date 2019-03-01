#include <iostream>
#include "KetMap.h"
#include "FnMap.h"

FnMap fn_map;

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
