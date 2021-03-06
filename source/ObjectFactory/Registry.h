#pragma once

class IContainer;

class Registry
{
public:
	virtual ~Registry() = default;

	virtual void Register(_Inout_ IContainer &container) const = 0;
};
