#pragma once

#include <tchar.h>
#include <string>

#include "InstantiatorFactory.h"
#include "Lifetimes.h"
#include "Registry.h"

class IInstantiator;

class IContainer
{
public:
	virtual ~IContainer();

	virtual void Initialize(const Registry &registry) = 0;

	template <class TInterface, class TImplementation>
	void Register(_In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot register types that do not have an inheritence relation.");

		std::shared_ptr<IInstantiator> pImplementationCreator = InstantiatorFactory::CreateInstantiator<TImplementation>();

		std::string interfaceTypeName = typeid (TInterface).name();

		Register(interfaceTypeName.c_str(), pImplementationCreator, lifetime);
	};

	template <class TConcreteClass>
	void Register(_In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		Register<TConcreteClass, TConcreteClass>(lifetime);
	};

	template <class T>
	std::shared_ptr<T> GetInstance() const
	{
		string interfaceTypeName = typeid (T).name();

		auto object = GetInstance(interfaceTypeName.c_str());

		return static_pointer_cast<T>(object);
	};

	template <class T>
	void Inject(_In_ const std::shared_ptr<T> &instance)
	{
		std::string interfaceTypeName = typeid (T).name();

		Inject(interfaceTypeName.c_str(), instance);
	};

	template <class T>
	void EjectAllInstancesOf()
	{
		string interfaceTypeName = typeid (T).name();

		EjectAllInstancesOf(interfaceTypeName.c_str());
	};

protected:
	virtual void Register(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime) = 0;
	virtual std::shared_ptr<void> GetInstance(_In_z_ LPCSTR interfaceTypeName) const = 0;
	virtual void Inject(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<void> &instance) = 0;
	virtual void EjectAllInstancesOf(_In_z_ LPCSTR interfaceTypeName) = 0;
};
