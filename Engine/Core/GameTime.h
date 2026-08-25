#pragma once
#include <cstdint>

namespace nu {
	class Time {
	public:
		Time();

		void Reset();
		void Tick();

		float GetTime() const { return TicksToSecs(m_currentTicks - m_startTicks); }
		float GetDeltaTime() const { return TicksToSecs(m_deltaTicks) * m_timeScale; }

		float TicksToSecs(uint64_t ticks) const { return (float)ticks / 1'000'000'000.0f; }

		void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
		float GetTimeScale() const { return m_timeScale; }

	private:
		float m_timeScale = 1.0f;

		uint64_t m_startTicks = 0;
		uint64_t m_prevTicks = 0;
		uint64_t m_currentTicks = 0;
		uint64_t m_deltaTicks = 0;
	};
}