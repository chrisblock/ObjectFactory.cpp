#pragma once

#include <memory>

#include "IContainer.h"

class Registry;

class ObjectFactory
{
public:
	static void Initialize(_In_ const Registry &registry);
	static void Clear();
	
	template <class T>
	static std::shared_ptr<T> GetInstance()
	{
		std::shared_ptr<T> result = _container->GetInstance<T>();

		return result;
	};

	template <class T>
	static void Inject(_In_ const std::shared_ptr<T> &instance)
	{
		_container->Inject<T>(instance);
	};

	template <class T>
	static void EjectAllInstancesOf()
	{
		_container->EjectAllInstancesOf<T>();
	};

private:
	ObjectFactory();

	static std::shared_ptr<IContainer> _container;
};
