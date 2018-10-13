#pragma once
#include "GL20.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"

namespace graphics_engine {

class GL20GUI : public GUIImpl
{
public:
    void Label(int, int, int, int, const char *);

    virtual ~GL20GUI()
    {}
};

}
