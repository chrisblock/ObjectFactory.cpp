#include "stdafx.h"

#include "TransientInstanceFactory.h"

#include "IInstantiator.h"

void swap(TransientInstanceFactory &left, TransientInstanceFactory &right)
{
	using std::swap;

	swap(left._instantiators, right._instantiators);
}

TransientInstanceFactory::TransientInstanceFactory()
{
}

TransientInstanceFactory::TransientInstanceFactory(const TransientInstanceFactory &other) :
	  _instantiators(other._instantiators)
{
}

TransientInstanceFactory::TransientInstanceFactory(TransientInstanceFactory &&other)
{
	swap(*this, other);
}

TransientInstanceFactory::~TransientInstanceFactory()
{
	_instantiators.clear();
}

TransientInstanceFactory &TransientInstanceFactory::operator =(TransientInstanceFactory other)
{
	swap(*this, other);

	return *this;
}

void TransientInstanceFactory::SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator)
{
	_instantiators[interfaceTypeName] = instantiator;
}

std::shared_ptr<void> TransientInstanceFactory::GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName)
{
	std::shared_ptr<void> result;

	auto instantiator = _instantiators.find(interfaceTypeName);

	if (instantiator == _instantiators.end())
	{
		std::string message(__LOC_A__ "Could not find instance creator for interface '");
		message += interfaceTypeName;
		message += "'.";

		std::exception e(message.c_str());

		throw e;
	}
	else
	{
		auto creator = instantiator->second;

		result = creator->CreateInstance(container);
	}

	return result;
}

void TransientInstanceFactory::RemoveInstance(_In_ const std::string &)
{
	// this method does nothing here because this instance factory does not keep track of instances it has created
}

void TransientInstanceFactory::Remove(_In_ const std::string &interfaceTypeName)
{
	_instantiators.erase(interfaceTypeName);
}
