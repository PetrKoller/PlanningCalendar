#include "./CCommand.h"

std::ostream &operator<<(std::ostream &out, const CCommand &rhs) {
    return rhs.print(out);
}
