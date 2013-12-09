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

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container) const
	{
		// when there are no variadic type arguments, the compiler will complain about unreferenced formal parameters
		UNREFERENCED_PARAMETER(container);

		std::shared_ptr<void> result = std::make_shared<TResult>(container.GetInstance<TArgs>()...);

		return result;
	};
};
