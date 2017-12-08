#include "Input.h"

//initialisation of static variables
std::vector<unsigned char> Input::m_keys;
std::vector<unsigned char> Input::m_downKeys;
std::vector<unsigned char> Input::m_upKeys;
std::vector<int> Input::m_mouseButtons;
std::vector<int> Input::m_downMouseButtons;
std::vector<int> Input::m_upMouseButtons;
float Input::m_xDiff = 0;
float Input::m_yDiff = 0;

float Input::GetMouseXDiff()
{
	return m_xDiff;
}

float Input::GetMouseYDiff()
{
	return m_yDiff;
}

bool Input::GetKey(unsigned char _key)
{
	//cycle through the active key vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<unsigned char>::iterator i = m_keys.begin(); i != m_keys.end(); i++)
	{
		if ((*i) == _key)
		{
			//if the key is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}

bool Input::GetKeyUp(unsigned char _key)
{
	//cycle through the up key vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<unsigned char>::iterator i = m_upKeys.begin(); i != m_upKeys.end(); i++)
	{
		if ((*i) == _key)
		{
			//if the key is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}

bool Input::GetKeyDown(unsigned char _key)
{
	//cycle through the down key vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<unsigned char>::iterator i = m_downKeys.begin(); i != m_downKeys.end(); i++)
	{
		if ((*i) == _key)
		{
			//if the key is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}

bool Input::GetMouseButton(int _buttonCode)
{
	//cycle through the active button vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<int>::iterator i = m_mouseButtons.begin(); i != m_mouseButtons.end(); i++)
	{
		if ((*i) == _buttonCode)
		{
			//if the button is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}

bool Input::GetMouseButtonDown(int _buttonCode)
{
	//cycle through the down button vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<int>::iterator i = m_downMouseButtons.begin(); i != m_downMouseButtons.end(); i++)
	{
		if ((*i) == _buttonCode)
		{
			//if the button is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}

bool Input::GetMouseButtonUp(int _buttonCode)
{
	//cycle through the up button vector to see if the specified key is contained within it
	bool retval = false;
	for (std::vector<int>::iterator i = m_upMouseButtons.begin(); i != m_upMouseButtons.end(); i++)
	{
		if ((*i) == _buttonCode)
		{
			//if the button is found set the return value to true and stop searching
			retval = true;
			break;
		}
	}
	return retval;
}