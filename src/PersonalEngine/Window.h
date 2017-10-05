#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window
{
public:
	static int GetWidth();
	static int GetHeight();
	static void Resize(int _width, int _height);
private:
	static int m_width;
	static int m_height;

};



#endif