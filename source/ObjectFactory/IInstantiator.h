#pragma once

#include <memory>

class IContainer;

class IInstantiator
{
public:
	virtual ~IInstantiator();

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) const = 0;
};
