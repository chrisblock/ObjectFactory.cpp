#pragma once

#include "IInstantiator.h"

#include <functional>
#include <memory>

class IContainer;

template <typename TResult, typename... TArgs>
class LambdaInstantiator : public IInstantiator
{
public:
	LambdaInstantiator()
	{
	};

	LambdaInstantiator(const std::function<std::shared_ptr<TResult> (const std::shared_ptr<TArgs> &...)> &lambda) :
		  _lambda(lambda)
	{
	};

	LambdaInstantiator(const LambdaInstantiator &other) :
		_lambda(other._lambda)
	{
	};


	LambdaInstantiator(LambdaInstantiator &&other) :
		LambdaInstantiator()
	{
		swap(*this, other);
	};

	virtual ~LambdaInstantiator()
	{
	};

	LambdaInstantiator &operator =(LambdaInstantiator other)
	{
		swap(*this, other);

		return *this;
	};

	friend void swap(LambdaInstantiator &left, LambdaInstantiator &right)
	{
		
	};

	virtual std::string GetType() const override
	{
		return typeid (TResult).name();
	};

	virtual std::vector<std::string> GetDependencies() const override
	{
		return { typeid (TArgs).name()... };
	};

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) const override
	{
		// when there are no variadic type arguments, the compiler will complain about unreferenced formal parameters
		container;

		std::shared_ptr<TResult> result = _lambda(container.GetInstance<TArgs>()...);

		return result;
	};

private:
	std::function<std::shared_ptr<TResult> (const std::shared_ptr<TArgs> &...)> _lambda;
};
