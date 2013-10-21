#pragma once

class IContainer;

class Registry
{
public:
	virtual ~Registry();

	virtual void Register(_Inout_ IContainer &container) const = 0;
};
