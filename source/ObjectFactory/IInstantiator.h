#pragma once

#include <memory>
#include <vector>

class IContainer;

class IInstantiator
{
public:
	virtual ~IInstantiator() = default;

	virtual std::string GetType() const = 0;
	virtual std::vector<std::string> GetDependencies() const = 0;
	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) const = 0;
};
