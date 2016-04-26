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

	VariadicArgumentInstantiator(VariadicArgumentInstantiator &&other) :
		  VariadicArgumentInstantiator()
	{
		swap(*this, other);
	};

	virtual ~VariadicArgumentInstantiator()
	{
	};

	VariadicArgumentInstantiator &operator =(VariadicArgumentInstantiator other)
	{
		swap(*this, other);

		return *this;
	};

	friend void swap(VariadicArgumentInstantiator &left, VariadicArgumentInstantiator &right)
	{
		using std::swap;

		left;
		right;
	};

	virtual std::string GetType() const override
	{
		return typeid (TResult).name();
	};

	virtual std::vector<std::string> GetDependencies() const override
	{
		return { typeid (TArgs).name()... };
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container) const override
	{
		// when there are no variadic type arguments, the compiler will complain about unreferenced formal parameters
		container;

		std::shared_ptr<void> result = std::make_shared<TResult>(container.GetInstance<TArgs>()...);

		return result;
	};
};
