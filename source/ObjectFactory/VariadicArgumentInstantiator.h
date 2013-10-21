#pragma once

#include "IInstantiator.h"

#include "IContainer.h"

template <class TResult, class... TArgs>
class VariadicArgumentInstantiator : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<void> result = make_shared<TResult>(container.GetInstance<TArgs>()...);

		return result;
	};
};
