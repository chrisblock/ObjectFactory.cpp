#pragma once

#include <memory>

#include "IContainer.h"

class Registry;

class ObjectFactory
{
public:
	ObjectFactory() = delete;
	ObjectFactory(const ObjectFactory &other) = delete;
	ObjectFactory(ObjectFactory &&other) = delete;
	~ObjectFactory() = delete;

	ObjectFactory &operator =(ObjectFactory other) = delete;

	static void Initialize(_In_ const Registry &registry);
	static void Clear();
	
	template <typename T>
	static std::shared_ptr<T> GetInstance()
	{
		std::shared_ptr<T> result = _container->GetInstance<T>();

		return result;
	};

	template <typename T>
	static void Inject(_In_ const std::shared_ptr<T> &instance)
	{
		_container->Inject<T>(instance);
	};

	template <typename T>
	static void EjectAllInstancesOf()
	{
		_container->EjectAllInstancesOf<T>();
	};

private:
	static std::shared_ptr<IContainer> _container;
};
