#include "lib.h"

namespace non_standard_member_vars {

void fn([[maybe_unused]] NonStandard ns) {}

void fn([[maybe_unused]] StandardClass sc) {}

} // namespace non_standard_member_vars