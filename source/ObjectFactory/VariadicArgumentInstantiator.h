#pragma once

#include "IInstantiator.h"

#include "IContainer.h"

template <typename TResult, typename TArg1 = void, typename TArg2 = void, typename TArg3 = void, typename TArg4 = void, typename TArg5 = void, typename TArg6 = void, typename TArg7 = void, typename TArg8 = void, typename TArg9 = void, typename TArg10 = void>
class VariadicArgumentInstantiator : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();
		std::shared_ptr<TArg6> arg6 = container.GetInstance<TArg6>();
		std::shared_ptr<TArg7> arg7 = container.GetInstance<TArg7>();
		std::shared_ptr<TArg8> arg8 = container.GetInstance<TArg8>();
		std::shared_ptr<TArg9> arg9 = container.GetInstance<TArg9>();
		std::shared_ptr<TArg10> arg10 = container.GetInstance<TArg10>();

		//std::shared_ptr<void> result(new TResult(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10), &IInstantiator::Delete<TResult>);
		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);

		return result;
	};
};

template <typename TResult>
class VariadicArgumentInstantiator<TResult, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &)
	{
		//std::shared_ptr<void> result(new TResult(), &IInstantiator::Delete<TResult>);
		std::shared_ptr<void> result = make_shared<TResult>();

		return result;
	};
};

template <typename TResult, typename TArg1>
class VariadicArgumentInstantiator<TResult, TArg1, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();
		std::shared_ptr<TArg6> arg6 = container.GetInstance<TArg6>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5, arg6);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();
		std::shared_ptr<TArg6> arg6 = container.GetInstance<TArg6>();
		std::shared_ptr<TArg7> arg7 = container.GetInstance<TArg7>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5, arg6, arg7);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();
		std::shared_ptr<TArg6> arg6 = container.GetInstance<TArg6>();
		std::shared_ptr<TArg7> arg7 = container.GetInstance<TArg7>();
		std::shared_ptr<TArg8> arg8 = container.GetInstance<TArg8>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);

		return result;
	};
};

template <typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>
class VariadicArgumentInstantiator<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, void> : public IInstantiator
{
public:
	virtual ~VariadicArgumentInstantiator()
	{
	};

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container)
	{
		std::shared_ptr<TArg1> arg1 = container.GetInstance<TArg1>();
		std::shared_ptr<TArg2> arg2 = container.GetInstance<TArg2>();
		std::shared_ptr<TArg3> arg3 = container.GetInstance<TArg3>();
		std::shared_ptr<TArg4> arg4 = container.GetInstance<TArg4>();
		std::shared_ptr<TArg5> arg5 = container.GetInstance<TArg5>();
		std::shared_ptr<TArg6> arg6 = container.GetInstance<TArg6>();
		std::shared_ptr<TArg7> arg7 = container.GetInstance<TArg7>();
		std::shared_ptr<TArg8> arg8 = container.GetInstance<TArg8>();
		std::shared_ptr<TArg9> arg9 = container.GetInstance<TArg9>();

		std::shared_ptr<void> result = make_shared<TResult>(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);

		return result;
	};
};
