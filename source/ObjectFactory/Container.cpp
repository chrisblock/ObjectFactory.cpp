#include "stdafx.h"

#include "Container.h"

#include "Lifetimes.h"
#include "Registry.h"
#include "SingletonInstanceFactory.h"
#include "ThreadScopeInstanceFactory.h"
#include "TransientInstanceFactory.h"

Container::Container() :
	  _factoriesByLifetime()
	, _factoriesByTypeName()
	, _injectedInstances()
{
	_factoriesByLifetime[Lifetimes::Singleton] = std::make_shared<SingletonInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Thread] = std::make_shared<ThreadScopeInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Transient] = std::make_shared<TransientInstanceFactory>();
}

Container::Container(const Container &other) :
	  _factoriesByLifetime(other._factoriesByLifetime)
	, _factoriesByTypeName(other._factoriesByTypeName)
	, _injectedInstances(other._injectedInstances)
{
}

Container::~Container()
{
}

Container &Container::operator =(const Container &other)
{
	if (this != &other)
	{
		_factoriesByLifetime = other._factoriesByLifetime;
		_factoriesByTypeName = other._factoriesByTypeName;
		_injectedInstances = other._injectedInstances;
	}

	return *this;
}

void Container::Initialize(_In_ const Registry &registry)
{
	registry.Register(*this);
}

void Container::Register(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime)
{
	auto pFactoryPair = _factoriesByLifetime.find(lifetime);

	if (pFactoryPair == _factoriesByLifetime.end())
	{
		std::string message(__LOC_A__ "Could not find factory for lifetime '");
		message += Lifetimes::GetName(lifetime);
		message += "'.";

		std::exception e(message.c_str());

		throw e;
	}
	else
	{
		Remove(interfaceTypeName);

		std::shared_ptr<IInstanceFactory> pFactory = pFactoryPair->second;

		pFactory->SetCreationStrategy(interfaceTypeName, implementationCreator);

		_factoriesByTypeName[interfaceTypeName] = pFactory;
	}
}

void Container::Remove(_In_z_ const char *interfaceTypeName)
{
	_factoriesByLifetime[Lifetimes::Singleton]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Thread]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Transient]->Remove(interfaceTypeName);
}

std::shared_ptr<void> Container::GetInstance(_In_z_ const char *interfaceTypeName) const
{
	std::shared_ptr<void> result;

	auto injectedItem = _injectedInstances.find(interfaceTypeName);

	if (injectedItem != _injectedInstances.end())
	{
		result = injectedItem->second;
	}
	else
	{
		auto pFactoryPair = _factoriesByTypeName.find(interfaceTypeName);

		if (pFactoryPair == _factoriesByTypeName.end())
		{
			std::string message(__LOC_A__ "Could not find instance factory for interface '");
			message += interfaceTypeName;
			message += "'.";

			std::exception e(message.c_str());

			throw e;
		}
		else
		{
			std::shared_ptr<IInstanceFactory> pFactory = pFactoryPair->second;

			result = pFactory->GetInstance(*this, interfaceTypeName);
		}
	}

	return result;
}

void Container::Inject(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<void> &instance)
{
	_injectedInstances[interfaceTypeName] = instance;
}

void Container::EjectAllInstancesOf(_In_z_ const char *interfaceTypeName)
{
	_injectedInstances.erase(interfaceTypeName);

	for (auto iter = _factoriesByLifetime.cbegin(); iter != _factoriesByLifetime.cend(); iter++)
	{
		iter->second->RemoveInstance(interfaceTypeName);
	}
}
