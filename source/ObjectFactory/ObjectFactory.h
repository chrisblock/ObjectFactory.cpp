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

	template <typename T>
	static void Inject(const std::shared_ptr<T> &instance)
	{
		_container->Inject<T>(instance);
	};

	template <typename T>
	static void EjectAllInstancesOf()
	{
		_container->EjectAllInstancesOf<T>();
	};

private:
	ObjectFactory();

	static std::shared_ptr<IContainer> _container;
};
