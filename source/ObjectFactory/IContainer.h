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
		static_assert(std::has_virtual_destructor<TInterface>::value, "Type does not have a virtual destuctor. It cannot be registered with ObjectFactory.");
		static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot register types that do not have an inheritence relation.");
		static_assert(std::is_abstract<TImplementation>::value == false, "Cannot register an abstract class with ObjectFactory.");

		std::shared_ptr<IInstantiator> pInstantiator = InstantiatorFactory::CreateInstantiator<TImplementation>();

		std::string interfaceTypeName = typeid (TInterface).name();

		Register(interfaceTypeName, pInstantiator, lifetime);
	};

	template <typename TConcreteClass>
	void Register(_In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		static_assert(std::is_abstract<TConcreteClass>::value == false, "Cannot register an abstract class with ObjectFactory.");

		Register<TConcreteClass, TConcreteClass>(lifetime);
	};

	template <typename TInterface>
	void Register(_In_ const std::function<std::shared_ptr<TInterface> (const IContainer &)> &lambda, _In_ const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		std::string interfaceTypeName = typeid (TInterface).name();

		std::shared_ptr<IInstantiator> pInstantiator = InstantiatorFactory::CreateInstantiator<TInterface>(lambda);

		Register(interfaceTypeName, pInstantiator, lifetime);
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

		EjectAllInstancesOf(interfaceTypeName);
	};

protected:
	virtual void Register(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime) = 0;
	virtual std::shared_ptr<void> GetInstance(_In_ const std::string &interfaceTypeName) const = 0;
	virtual void Inject(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<void> &instance) = 0;
	virtual void EjectAllInstancesOf(_In_ const std::string &interfaceTypeName) = 0;
};
