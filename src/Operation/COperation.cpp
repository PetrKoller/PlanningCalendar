#include "COperation.h"

std::ostream &operator<<(std::ostream &out, const COperation &rhs) {
    return rhs.print(out);
}
