#pragma once

#include <memory>

class IContainer;

class IInstantiator
{
public:
	virtual ~IInstantiator();

	virtual std::shared_ptr<void> CreateInstance(_In_ const IContainer &container) = 0;

protected:
	template <class T>
	static void Delete(_In_ void *instance)
	{
		T *pointer = static_cast<T *>(instance);

		delete pointer;
	};
};
