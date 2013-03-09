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

	template <typename TInterface, typename TImplementation>
	void Register(const Lifetimes::Lifetime lifetime = Lifetimes::Transient)
	{
		static_assert(std::is_base_of<TInterface, TImplementation>::value, "Cannot register types that do not have an inheritence relation." );

		std::shared_ptr<IInstantiator> pImplementationCreator = InstantiatorFactory::CreateInstantiator<TImplementation>();

		std::basic_string<TCHAR> interfaceTypeName = ::ConvertToTString(typeid (TInterface).name());

		Register(interfaceTypeName.c_str(), pImplementationCreator, lifetime);
	};

	template <typename T>
	shared_ptr<T> GetInstance() const
	{
		auto interfaceTypeName = ::ConvertToTString(typeid (T).name());

		auto object = GetInstance(interfaceTypeName.c_str());

		return static_pointer_cast<T>(object);
	};

protected:
	virtual void Register(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &implementationCreator, const Lifetimes::Lifetime lifetime) = 0;
	virtual std::shared_ptr<void> GetInstance(LPCTSTR interfaceTypeName) const = 0;
};
