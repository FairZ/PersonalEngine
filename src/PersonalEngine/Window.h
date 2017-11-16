#ifndef _WINDOW_H_
#define _WINDOW_H_

/// \brief Handler for windowing
class Window
{
	friend class Engine;
public:
	static int GetWidth();
	static int GetHeight();
private:
	static void Resize(int _width, int _height);
	static int m_width;
	static int m_height;

};



#endif