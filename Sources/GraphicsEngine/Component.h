#pragma once
#include <stdlib.h>

namespace graphics_engine {

class Object;

class Component
{
public:
	Component() 
	{
        m_pObject = nullptr;
	}

	virtual ~Component() {}

	void Init(Object * pObject)
	{
		m_pObject = pObject;
	}
	
    Object * GetObjectPtr()
	{
		return m_pObject;
	}

    const Object * GetConstObjectPtr() const
    {
        return m_pObject;
    }

	virtual void Update() { }

protected:
	Object * m_pObject;
};

}
