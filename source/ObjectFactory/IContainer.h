#pragma once

#include <functional>
#include <memory>
#include <string>

#include "InstantiatorFactory.h"
#include "Lifetimes.h"

class IInstantiator;
class Registry;

class IContainer
{
public:
	virtual ~IContainer();

	virtual void Initialize(const Registry &registry) = 0;

	template <typename TInterface, class TImplementation>
	void Register(_In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot register types that do not have an inheritence relation.");

		std::shared_ptr<IInstantiator> pInstantiator = InstantiatorFactory::CreateInstantiator<TImplementation>();

		std::string interfaceTypeName = typeid (TInterface).name();

		Register(interfaceTypeName.c_str(), pInstantiator, lifetime);
	};

	template <typename TConcreteClass>
	void Register(_In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		Register<TConcreteClass, TConcreteClass>(lifetime);
	};

	template <typename TInterface>
	void Register(_In_ const std::function<std::shared_ptr<TInterface> (const IContainer &)> &lambda, _In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		std::string interfaceTypeName = typeid (TInterface).name();

		std::shared_ptr<IInstantiator> pInstantiator = InstantiatorFactory::CreateInstantiator<TInterface>(lambda);

		Register(interfaceTypeName.c_str(), pInstantiator, lifetime);
	};

	template <typename T>
	std::shared_ptr<T> GetInstance() const
	{
		std::string interfaceTypeName = typeid (T).name();

		auto object = GetInstance(interfaceTypeName.c_str());

		return std::static_pointer_cast<T>(object);
	};

	template <typename T>
	void Inject(_In_ const std::shared_ptr<T> &instance)
	{
		std::string interfaceTypeName = typeid (T).name();

		Inject(interfaceTypeName.c_str(), instance);
	};

	template <typename T>
	void EjectAllInstancesOf()
	{
		std::string interfaceTypeName = typeid (T).name();

		EjectAllInstancesOf(interfaceTypeName.c_str());
	};

protected:
	virtual void Register(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime) = 0;
	virtual std::shared_ptr<void> GetInstance(_In_z_ const char *interfaceTypeName) const = 0;
	virtual void Inject(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<void> &instance) = 0;
	virtual void EjectAllInstancesOf(_In_z_ const char *interfaceTypeName) = 0;
};
