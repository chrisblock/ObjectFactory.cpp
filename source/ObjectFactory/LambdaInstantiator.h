#pragma once

#include "IInstantiator.h"

#include <functional>
#include <memory>

class IContainer;

class LambdaInstantiator : public IInstantiator
{
public:
	LambdaInstantiator(const std::function<std::shared_ptr<void> (const IContainer &)> &lambda);
	virtual ~LambdaInstantiator();

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) const;

private:
	std::function<std::shared_ptr<void> (const IContainer &)> _lambda;
};
