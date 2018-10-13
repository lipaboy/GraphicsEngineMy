#pragma once

namespace graphics_engine {

class GUIImpl
{
public:
	virtual void Label(int x, int y, int w, int h, const char * pText) = 0;
};

}
