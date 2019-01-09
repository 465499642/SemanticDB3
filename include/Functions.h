#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Ket.h"


std::vector<std::string> split(const std::string& s, const std::string& delimiter);
std::string join(const std::vector<std::string>& v, const std::string& delimiter);
bool double_eq(const double v1, const double v2);

Ket extract_head(Ket k);
Ket extract_tail(Ket k);
Ket extract_category(Ket k);
Ket extract_value(Ket k);


#endif
