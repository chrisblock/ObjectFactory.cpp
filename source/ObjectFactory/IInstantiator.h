#pragma once

#include <memory>

class IContainer;

class IInstantiator
{
public:
	virtual ~IInstantiator();

	virtual std::shared_ptr<void> CreateInstance(const IContainer &container) = 0;

protected:
	template <typename T>
	static void Delete(void *instance)
	{
		T *pointer = static_cast<T *>(instance);

		delete pointer;
	};
};
