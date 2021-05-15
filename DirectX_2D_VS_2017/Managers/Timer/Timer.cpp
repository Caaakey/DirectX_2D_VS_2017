#include "stdafx.h"
#include "Timer.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

Timer::Timer()
	:m_CurrentTime(0), m_FpsFrameCount(0), m_FpsTimeElapsed(0), m_FrameRate(0),
	m_TimeElapsed(0), m_WorldTime(0)
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_PreriodTime)) {
		m_SupportPerformanceFrequency = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);
		m_TimeScale = 1.0f / m_PreriodTime;
	}
	else {
		m_SupportPerformanceFrequency = false;
		m_LastTime = timeGetTime();
		m_TimeScale = 0.001f;
	}
}

void Timer::UpdateTime(float frameLock)
{
	if (m_SupportPerformanceFrequency) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
	else m_CurrentTime = timeGetTime();

	m_TimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

	if (frameLock > 0.0f) {
		while (m_TimeElapsed < (1.0f / frameLock)) {
			if (m_SupportPerformanceFrequency) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
			else m_CurrentTime = timeGetTime();

			m_TimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;
		}
	}

	m_LastTime = m_CurrentTime;
	m_FpsFrameCount++;
	m_FpsTimeElapsed += m_TimeElapsed;
	m_WorldTime += m_TimeElapsed;

	if (m_FpsTimeElapsed > 1.0f) {
		m_FrameRate = m_FpsFrameCount;
		m_FpsFrameCount = 0;
		m_FpsTimeElapsed = 0.0f;
	}
}

void Timer::DrawFrame()
{
#ifdef _DEBUG
	wchar_t wstr[256] = { 0, };
	static wchar_t msg[] = L"WorldTime : %.2f\nFrameCount : %f\nFPS : %d";

	_stprintf_s(wstr, msg, m_WorldTime, m_TimeElapsed, m_FrameRate);
	_RenderTarget->DrawTextW(
		wstr,
		static_cast<UINT32>(wcslen(wstr)),
		_Font->Default(),
		D2D1::RectF(0.0f, 0.0f, 200.0f, 100.0f),
		_RenderDevice->GetBrush());
#endif
}
