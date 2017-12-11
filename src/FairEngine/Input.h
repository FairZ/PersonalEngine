#ifndef _INPUT_H_
#define _INPUT_H_
#include <vector>

/// \brief Stores and handles checking against keyboard and mouse inputs
class Input
{
	friend class Engine;
public:
	static bool GetKey(unsigned char _key);
	static bool GetKeyUp(unsigned char _key);
	static bool GetKeyDown(unsigned char _key);
	static bool GetMouseButton(int _buttoncode);
	static bool GetMouseButtonDown(int _buttoncode);
	static bool GetMouseButtonUp(int _buttoncode);
	static float GetMouseXDiff();
	static float GetMouseYDiff();

private:
	static std::vector<unsigned char> m_keys;
	static std::vector<unsigned char> m_downKeys;
	static std::vector<unsigned char> m_upKeys;
	static std::vector<int> m_mouseButtons;
	static float m_xDiff;
	static float m_yDiff;
	static std::vector<int> m_downMouseButtons;
	static std::vector<int> m_upMouseButtons;

};


#endif