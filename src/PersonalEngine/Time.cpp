#include "Time.h"

float Time::m_deltaTime=0.0f;
int Time::m_lastTime=0;
float Time::m_fixedDeltaTime=0.0f;

int Time::GetDeltaTimeMS()
{
	return m_deltaTime * 1000;
}

float Time::GetDeltaTimeSec()
{
	return m_deltaTime;
}

int Time::GetFixedDeltaTimeMS()
{
	return m_fixedDeltaTime * 1000;
}

float Time::GetFixedDeltaTimeSec()
{
	return m_fixedDeltaTime;
}