/**
 * This assert helper is taken from DuckDB
 * https://github.com/duckdb/duckdb
 */

#include <exception>
#pragma once

namespace thesis {
void AssertInternal(bool condition, const char *condition_name, const char *file, int linenr);
}

#define D_ASSERT(condition) thesis::AssertInternal(bool(condition), #condition, __FILE__, __LINE__)
