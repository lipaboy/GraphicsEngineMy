#pragma once

namespace graphics_engine {

class Task
{
public:
	virtual ~Task() { }

	virtual void Init()		{ }
	virtual void Update()	{ }
};

}
