#pragma once

#include <memory>

#include "IInstantiator.h"

template <class T>
class DefaultConstructorInstantiator : public IInstantiator
{
public:
	virtual ~DefaultConstructorInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &)
	{
		std::shared_ptr<void> result = make_shared<T>();

		return result;
	};
};
