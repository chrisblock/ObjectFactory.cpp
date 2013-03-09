#include "stdafx.h"

#include "Container.h"

#include "Exception.h"
#include "Lifetimes.h"
#include "TransientInstanceFactory.h"
#include "SingletonInstanceFactory.h"
#include "ThreadScopeInstanceFactory.h"

Container::Container()
{
	_factoriesByLifetime[Lifetimes::Transient] = make_shared<TransientInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Singleton] = make_shared<SingletonInstanceFactory>();
	_factoriesByLifetime[Lifetimes::Thread] = make_shared<ThreadScopeInstanceFactory>();
}

Container::~Container()
{
	_factoriesByLifetime.clear();

	_factoriesByTypeName.clear();
}

void Container::Initialize(const Registry &registry)
{
	registry.Register(*this);
}

void Container::Register(LPCTSTR interfaceTypeName, const shared_ptr<IInstantiator> &implementationCreator, const Lifetimes::Lifetime lifetime)
{
	auto pFactoryPair = _factoriesByLifetime.find(lifetime);

	if (pFactoryPair == _factoriesByLifetime.end())
	{
		basic_string<TCHAR> message(__LOC__ _T("Could not find factory for lifetime '"));
		message += Lifetimes::GetName(lifetime);
		message += _T("'.");

		throw new Exception(message.c_str());
	}
	else
	{
		Remove(interfaceTypeName);

		shared_ptr<IInstanceFactory> pFactory = pFactoryPair->second;

		pFactory->SetCreationStrategy(interfaceTypeName, implementationCreator);

		_factoriesByTypeName[interfaceTypeName] = pFactory;
	}
}

void Container::Remove(LPCTSTR interfaceTypeName)
{
	_factoriesByLifetime[Lifetimes::Transient]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Singleton]->Remove(interfaceTypeName);
	_factoriesByLifetime[Lifetimes::Thread]->Remove(interfaceTypeName);
}

shared_ptr<void> Container::GetInstance(LPCTSTR interfaceTypeName) const
{
	shared_ptr<void> result;

	auto pFactoryPair = _factoriesByTypeName.find(interfaceTypeName);

	if (pFactoryPair == _factoriesByTypeName.end())
	{
		basic_string<TCHAR> message(__LOC__ _T("Could not find instance factory for interface '"));
		message += interfaceTypeName;
		message += _T("'.");

		throw new Exception(message.c_str());
	}
	else
	{
		shared_ptr<IInstanceFactory> pFactory = pFactoryPair->second;

		result = pFactory->GetInstance(*this, interfaceTypeName);
	}

	return result;
}
