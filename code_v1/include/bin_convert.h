#include <cstdint>
#include <string>

inline void convert (uint32_t val) {
	std::string s = "00000000000000000000000000000000";
	int i = 31;
	while (val) {
		if (val & 1) {
			s[i] += 1;
		}
		val >>= 1;
		i--;
	}
	puts(s.c_str());
}