#pragma once

class IContainer;

class Registry
{
public:
	virtual ~Registry();

	virtual void Register(IContainer &container) const = 0;
};
