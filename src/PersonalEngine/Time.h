#ifndef _TIME_H_
#define _TIME_H_

class Time
{
	friend class Engine;
public:
	static int GetDeltaTimeMS();
	static float GetDeltaTimeSec();
	static int GetFixedDeltaTimeMS();
	static float GetFixedDeltaTimeSec();
private:
	static float m_deltaTime;
	static int m_lastTime;
	static float m_fixedDeltaTime;
};


#endif