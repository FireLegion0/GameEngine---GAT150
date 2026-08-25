#pragma once

namespace nu {
	constexpr float Pi = 3.1415926535897932384626433832795f;
	constexpr float TwoPi = 3.1415926535897932384626433832795f * 2.0f;
	constexpr float HalfPi = 3.1415926535897932384626433832795f * 0.5f;

	constexpr float RadToDeg = 180.0f / Pi;
	constexpr float DegToRad = Pi / 180.0f;

	template<typename T>
	T Min(T a, T b) { return (a < b) ? a : b; }
	template<typename T>
	T Max(T a, T b) { return (a > b) ? a : b; }

	template<typename T>
	T Wrap(T min, T max, T value) {
		if (value < min) value = max;
		if (value > max) value = min;
		return value;
	}

	template<typename T>
	T Clamp(T min, T max, T value) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}