#pragma once

class Timer
{
public:
	Timer();
	static Timer* Get() {
		static Timer instance;
		return &instance;
	}

private:
	bool m_SupportPerformanceFrequency;

	float m_TimeScale;
	float m_TimeElapsed;
	__int64 m_PreriodTime;
	__int64 m_LastTime;
	__int64 m_CurrentTime;

	unsigned long m_FrameRate;
	unsigned long m_FpsFrameCount;

	float m_FpsTimeElapsed;
	float m_WorldTime;

public:
	const bool SupportPerformanceFrequency() const { return m_SupportPerformanceFrequency; }
	inline float GetWorldTime(void) const { return m_WorldTime; }
	inline float GetFPSTime(void) { return (float)m_FrameRate; }
	inline float GetElapsedTime(void) const { return m_TimeElapsed; }

public:
	void UpdateTime(float frameLock = 60.0f);
	void DrawFrame();

};

#define _Timer Timer::Get()