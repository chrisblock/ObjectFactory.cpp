#pragma once

#include <memory>

#include "IContainer.h"
#include "Registry.h"

class ObjectFactory
{
public:
	static void Initialize(const Registry &registry);
	static void Clear();
	
	template <typename T>
	static std::shared_ptr<T> GetInstance()
	{
		std::shared_ptr<T> result = _container->GetInstance<T>();

		return result;
	};

private:
	ObjectFactory();

	static std::shared_ptr<IContainer> _container;
};
