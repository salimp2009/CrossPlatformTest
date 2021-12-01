#include "RangesHeaders.hpp"
#include "ConstexprString.hpp"

template<class... Args>
string  format(std::string_view fmt, const Args&... args);