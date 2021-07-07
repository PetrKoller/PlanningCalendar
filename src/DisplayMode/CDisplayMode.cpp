//
// Created by progtest on 27.05.21.
//

#include "./CDisplayMode.h"


std::ostream &operator<<(std::ostream &out, const CDisplayMode &rhs) {
    return rhs.print(out);
}
