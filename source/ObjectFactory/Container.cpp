#include "stdafx.h"

#include "Container.h"

#include "Lifetimes.h"
#include "RegisteredComponent.h"
#include "Registry.h"
#include "SingletonInstanceFactory.h"
#include "ThreadScopeInstanceFactory.h"
#include "TransientInstanceFactory.h"

void swap(_Inout_ Container &left, _Inout_ Container &right)
{
	using std::swap;

	swap(left._factoriesByLifetime, right._factoriesByLifetime);
	swap(left._factoriesByTypeName, right._factoriesByTypeName);
	swap(left._injectedInstances, right._injectedInstances);
}

Container::Container() :
	  _injectedInstances()
	, _factoriesByLifetime()
	, _factoriesByTypeName()
{
	_factoriesByLifetime[Lifetimes::Singleton] = std::make_shared<SingletonInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Thread] = std::make_shared<ThreadScopeInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Transient] = std::make_shared<TransientInstanceFactory>();
}

Container::Container(_In_ const Registry &registry) :
	  Container()
{
	registry.Register(*this);
}

Container::Container(_In_ const Container &other) :
	  _injectedInstances(other._injectedInstances)
	, _factoriesByLifetime(other._factoriesByLifetime)
	, _factoriesByTypeName(other._factoriesByTypeName)
{
}

Container::Container(_In_ Container &&other) :
	  Container()
{
	swap(*this, other);
}

Container::~Container()
{
}

Container &Container::operator =(_In_ Container other)
{
	swap(*this, other);

	return *this;
}

void Container::Initialize(_In_ const Registry &registry)
{
	registry.Register(*this);
}

std::vector<RegisteredComponent> Container::GetRegisteredComponents() const
{
	std::vector<RegisteredComponent> result;

	for (const std::pair<Lifetimes::Lifetime, std::shared_ptr<IInstanceFactory>> &pair : _factoriesByLifetime)
	{
		std::vector<RegisteredComponent> components = pair.second->GetRegisteredComponents();

		result.insert(result.end(), components.cbegin(), components.cend());
	}

	return result;
}

void Container::Register(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime)
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

void Container::Remove(_In_ const std::string &interfaceTypeName)
{
	_factoriesByLifetime[Lifetimes::Singleton]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Thread]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Transient]->Remove(interfaceTypeName);
}

std::shared_ptr<void> Container::GetInstance(_In_ const std::string &interfaceTypeName) const
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

void Container::Inject(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<void> &instance)
{
	_injectedInstances[interfaceTypeName] = instance;
}

void Container::EjectAllInstancesOf(_In_ const std::string &interfaceTypeName)
{
	_injectedInstances.erase(interfaceTypeName);

	for (const auto &item : _factoriesByLifetime)
	{
		item.second->RemoveInstance(interfaceTypeName);
	}
}
