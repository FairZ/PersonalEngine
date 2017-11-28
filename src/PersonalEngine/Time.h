#ifndef _TIME_H_
#define _TIME_H_

class Time
{
	friend class Engine;
public:
	static int GetDeltaTimeMS();
	static float GetDeltaTimeSec();
private:
	static float m_deltaTime;
	static int m_lastTime;
};


#endif