#pragma once

#include <tchar.h>
#include <string>

#include "IInstantiator.h"
#include "InstantiatorFactory.h"
#include "Lifetimes.h"
#include "Registry.h"
#include "StringHelpers.h"

class IContainer
{
public:
	virtual ~IContainer();

	virtual void Initialize(const Registry &registry) = 0;

	template <typename TInterface, typename TImplementation>
	void Register(const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot register types that do not have an inheritence relation.");

		std::shared_ptr<IInstantiator> pImplementationCreator = InstantiatorFactory::CreateInstantiator<TImplementation>();

		std::basic_string<TCHAR> interfaceTypeName = ::ConvertToTString(typeid (TInterface).name());

		Register(interfaceTypeName.c_str(), pImplementationCreator, lifetime);
	};

	template <typename TConcreteClass>
	void Register(const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		Register<TConcreteClass, TConcreteClass>(lifetime);
	};

	template <typename T>
	std::shared_ptr<T> GetInstance() const
	{
		auto interfaceTypeName = ::ConvertToTString(typeid (T).name());

		auto object = GetInstance(interfaceTypeName.c_str());

		return static_pointer_cast<T>(object);
	};

	template <typename T>
	void Inject(const std::shared_ptr<T> &instance)
	{
		auto interfaceTypeName = ::ConvertToTString(typeid (T).name());

		Inject(interfaceTypeName.c_str(), instance);
	};

	template <typename T>
	void EjectAllInstancesOf()
	{
		auto interfaceTypeName = ::ConvertToTString(typeid (T).name());

		EjectAllInstancesOf(interfaceTypeName.c_str());
	};

protected:
	virtual void Register(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &implementationCreator, const Lifetimes::Lifetime lifetime) = 0;
	virtual std::shared_ptr<void> GetInstance(LPCTSTR interfaceTypeName) const = 0;
	virtual void Inject(LPCTSTR interfaceTypeName, const shared_ptr<void> &instance) = 0;
	virtual void EjectAllInstancesOf(LPCTSTR interfaceTypeName) = 0;
};
