#ifndef HELPERS_ASSERT_HPP
#define HELPERS_ASSERT_HPP

/**
 * This assert helper is taken from DuckDB
 * https://github.com/duckdb/duckdb
 */

#include <exception>

namespace thesis {
namespace helpers {

void AssertInternal(bool condition, const char *condition_name, const char *file, int linenr);

}
}

#define D_ASSERT(condition) thesis::AssertInternal(bool(condition), #condition, __FILE__, __LINE__)

#endif // HELPERS_ASSERT_HPP
