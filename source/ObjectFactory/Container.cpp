#include "stdafx.h"

#include "Container.h"

#include "Lifetimes.h"
#include "TransientInstanceFactory.h"
#include "SingletonInstanceFactory.h"
#include "ThreadScopeInstanceFactory.h"

Container::Container()
{
	_factoriesByLifetime[Lifetimes::Transient] = std::make_shared<TransientInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Singleton] = std::make_shared<SingletonInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Thread] = std::make_shared<ThreadScopeInstanceFactory>();
}

Container::~Container()
{
	_factoriesByLifetime.clear();

	_factoriesByTypeName.clear();
}

void Container::Initialize(_In_ const Registry &registry)
{
	registry.Register(*this);
}

void Container::Register(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime)
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

void Container::Remove(_In_z_ LPCSTR interfaceTypeName)
{
	_factoriesByLifetime[Lifetimes::Transient]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Singleton]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Thread]->Remove(interfaceTypeName);
}

std::shared_ptr<void> Container::GetInstance(_In_z_ LPCSTR interfaceTypeName) const
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

void Container::Inject(_In_z_ LPCSTR interfaceTypeName, _In_ const std::shared_ptr<void> &instance)
{
	_injectedInstances[interfaceTypeName] = instance;
}

void Container::EjectAllInstancesOf(_In_z_ LPCSTR interfaceTypeName)
{
	_injectedInstances.erase(interfaceTypeName);

	// TODO: forward the Eject call on to each factory so that they can clear their object caches too??
}
