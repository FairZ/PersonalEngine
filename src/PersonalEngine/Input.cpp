#include "Input.h"

std::list<int> Input::m_keys;
std::list<int> Input::m_downKeys;
std::list<int> Input::m_upKeys;
std::list<int> Input::m_mouseButtons;
std::list<int> Input::m_downMouseButtons;
std::list<int> Input::m_upMouseButtons;

bool Input::GetKey(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_keys.begin(); i != m_keys.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}

bool Input::GetKeyUp(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_upKeys.begin(); i != m_upKeys.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}

bool Input::GetKeyDown(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_downKeys.begin(); i != m_downKeys.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}

bool Input::GetMouseButton(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_mouseButtons.begin(); i != m_mouseButtons.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}

bool Input::GetMouseButtonDown(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_downMouseButtons.begin(); i != m_downMouseButtons.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}

bool Input::GetMouseButtonUp(int _keycode)
{
	bool retval = false;
	for (std::list<int>::iterator i = m_upMouseButtons.begin(); i != m_upMouseButtons.end(); i++)
	{
		if ((*i) == _keycode)
		{
			retval = true;
		}
	}
	return retval;
}