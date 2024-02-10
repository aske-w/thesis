#include "helpers/assert.hpp"
#include <format>
#include <string>
#include <cstdlib>
namespace thesis {

class assertException : public std::exception {
private:
    std::unique_ptr<char*> msg;
public:
    explicit assertException(const char *condition_name, const char *file, int linenr)
    : std::exception() {
        auto fmt = "Assertion triggered in file \"%s\" on line %d: %s";
        auto linenr_str = std::to_string(linenr);
        auto approx_length = strlen(fmt) + strlen(file) + strlen(condition_name) + linenr_str.size();
        auto str_buffer = std::make_unique<char*>( new char[approx_length]);
        snprintf(*str_buffer, approx_length, fmt, file, linenr, condition_name);
    }
    const char * what() const noexcept override {
        return "";
    }
};

void AssertInternal(bool condition, const char *condition_name, const char *file, int linenr) {
#ifdef DISABLE_ASSERTIONS
	return;
#endif
	if (condition) {
		return;
	}
	throw assertException(condition_name, file, linenr);
}

}
