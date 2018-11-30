#pragma once
class observer
{
	observer() {}
	virtual ~observer() {}
	virtual void update() = 0;
};