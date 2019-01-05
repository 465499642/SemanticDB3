#ifndef BASERULE_H
#define BASERULE_H

#include <string>
#include "KetMap.h"

class BaseRule {
    private:

    public:
        virtual int type() = 0;
        virtual std::string to_string() = 0;
        virtual ulong size() = 0;
};

#endif
