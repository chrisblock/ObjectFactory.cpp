#include "stdafx.h"

#include "DefaultConstructorInstantiator.h"

//template <typename TResult, typename... TArgs>
//class VariadicInstanceCreator
//{
//public:
//	VariadicInstanceCreator()
//	{
//
//	};
//
//	virtual ~VariadicInstanceCreator()
//	{
//	};
//};

#include "IContainer.h"

template <typename TResult, typename TArg1>
class ArgumentConstructorInstantiator : public IInstantiator
{
public:
	virtual void *CreateInstance(const IContainer &container)
	{
		shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();

		shared_ptr<TResult> result(new TResult(arg1), &IInstantiator::Delete<TResult>);

		return result;
	};
};

/*
template <typename TResult, typename... TArgs>
class ArgumentConstructorInstantiator : public IInstantiator
{
public:
	virtual void *CreateInstance(const IContainer &container)
	{
		TResult *result = new TResult(container.GetInstance<Args>()...);

		return result;
	};
};
*/