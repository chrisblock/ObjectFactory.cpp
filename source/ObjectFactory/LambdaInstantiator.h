#pragma once

#include "IInstantiator.h"

#include <functional>
#include <memory>

class IContainer;

class LambdaInstantiator : public IInstantiator
{
public:
	LambdaInstantiator(const std::function<std::shared_ptr<void> (const IContainer &)> &lambda);
	LambdaInstantiator(const LambdaInstantiator &other);
	LambdaInstantiator(LambdaInstantiator &&other);
	virtual ~LambdaInstantiator();

	LambdaInstantiator &operator =(LambdaInstantiator other);

	friend void swap(LambdaInstantiator &left, LambdaInstantiator &right);

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) const override;

private:
	std::function<std::shared_ptr<void> (const IContainer &)> _lambda;
};

void swap(LambdaInstantiator &left, LambdaInstantiator &right);
