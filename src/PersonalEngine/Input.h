#ifndef _INPUT_H_
#define _INPUT_H_
#include <list>


class Input
{
public:
	static bool GetKey(int _keycode);
	static bool GetKeyUp(int _keycode);
	static bool GetKeyDown(int _keycode);
	static bool GetMouseButton(int _buttoncode);
	static bool GetMouseButtonDown(int _buttoncode);
	static bool GetMouseButtonUp(int _buttoncode);

private:
	static std::list<int> m_keys;
	static std::list<int> m_downKeys;
	static std::list<int> m_upKeys;
	static std::list<int> m_mouseButtons;
	static std::list<int> m_downMouseButtons;
	static std::list<int> m_upMouseButtons;

};


#endif