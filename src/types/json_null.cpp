#include "../../include/types/json_null.hpp"

std::string json_null::dump(int indent, int current_indent) const {
    std::ignore = indent;
    std::ignore = current_indent;
   
    return "null";
}

bool json_null::operator==(const json_null&) const {
    return true;
}

bool json_null::operator!=(const json_null& other) const {
    return !(*this == other);
}
