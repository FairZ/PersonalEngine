#include "Time.h"

float Time::m_deltaTime;
int Time::m_lastTime;

int Time::GetDeltaTimeMS()
{
	return m_deltaTime;
}

float Time::GetDeltaTimeSec()
{
	return m_deltaTime/1000;
}