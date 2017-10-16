#ifndef _INPUT_H_
#define _INPUT_H_
#include <vector>

/// \brief Input interface
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

private:
	static std::vector<unsigned char> m_keys;
	static std::vector<unsigned char> m_downKeys;
	static std::vector<unsigned char> m_upKeys;
	static std::vector<int> m_mouseButtons;
	static std::vector<int> m_downMouseButtons;
	static std::vector<int> m_upMouseButtons;

};


#endif