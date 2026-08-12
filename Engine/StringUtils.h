#pragma once
#include <string>
#include <iostream>

namespace nu {

	inline std::string ToLower(const std::string& str) {
		std::string lowerStr = str;
		for (auto& c : lowerStr) {
			c = std::tolower(c);
		}

		return lowerStr;
	}

	inline std::string ToUpper(const std::string& str) {
		std::string upperStr = str;
		for (auto& c : upperStr) {
			c = std::toupper(c);
		}

		return upperStr;
	}

	inline bool EqualsIgnoreCase(const std::string& str1, const std::string& str2) {
		// HELLO <-> HELL

		if (str1.size() != str2.size()) {
			return false;
		}

		return ToLower(str1) == ToLower(str2);
	}
}