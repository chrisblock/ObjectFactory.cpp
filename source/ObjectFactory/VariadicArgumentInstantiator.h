#pragma once

#include "IInstantiator.h"

#include "IContainer.h"

template <typename TResult, typename... TArgs>
class VariadicArgumentInstantiator : public IInstantiator
{
public:
	VariadicArgumentInstantiator()
	{
	};

	VariadicArgumentInstantiator(const VariadicArgumentInstantiator &other)
	{
		other;
	};

	VariadicArgumentInstantiator(VariadicArgumentInstantiator &&other)
	{
		other;
	};

	virtual ~VariadicArgumentInstantiator()
	{
	};

	VariadicArgumentInstantiator &operator =(VariadicArgumentInstantiator other)
	{
		other;

		return &this;
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container) const
	{
		// when there are no variadic type arguments, the compiler will complain about unreferenced formal parameters
		container;

		std::shared_ptr<void> result = std::make_shared<TResult>(container.GetInstance<TArgs>()...);

		return result;
	};
};
