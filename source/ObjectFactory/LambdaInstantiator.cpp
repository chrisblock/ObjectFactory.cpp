#include "stdafx.h"

#include "LambdaInstantiator.h"

LambdaInstantiator::LambdaInstantiator(const std::function<std::shared_ptr<void>(const IContainer &)> &lambda) :
	  _lambda(lambda)
{
}

LambdaInstantiator::~LambdaInstantiator()
{
}

std::shared_ptr<void> LambdaInstantiator::CreateInstance(_In_ const IContainer &container) const
{
	std::shared_ptr<void> result = _lambda(container);

	return result;
}
