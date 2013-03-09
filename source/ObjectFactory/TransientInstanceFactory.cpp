#include "stdafx.h"

#include "TransientInstanceFactory.h"

#include "Exception.h"

TransientInstanceFactory::~TransientInstanceFactory()
{
	_instanceCreators.clear();
}

void TransientInstanceFactory::SetCreationStrategy(LPCTSTR interfaceTypeName, const shared_ptr<IInstantiator> &instanceCreator)
{
	_instanceCreators[interfaceTypeName] = instanceCreator;
}

shared_ptr<void> TransientInstanceFactory::GetInstance(const IContainer &container, LPCTSTR interfaceTypeName)
{
	shared_ptr<void> result;

	auto instanceCreator = _instanceCreators.find(interfaceTypeName);

	if (instanceCreator == _instanceCreators.end())
	{
		basic_string<TCHAR> message(__LOC__ _T("Could not find instance creator for interface '"));
		message += interfaceTypeName;
		message += _T("'.");

		throw new Exception(message.c_str());
	}
	else
	{
		auto creator = instanceCreator->second;

		result = creator->CreateInstance(container);
	}

	return result;
}

void TransientInstanceFactory::Remove(LPCTSTR interfaceTypeName)
{
	_instanceCreators.erase(interfaceTypeName);
}
