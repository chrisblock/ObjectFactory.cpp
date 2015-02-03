#pragma once

#include <map>
#include <memory>
#include <string>

#include "IInstanceFactory.h"

class IInstantiator;

class TransientInstanceFactory : public IInstanceFactory
{
public:
	TransientInstanceFactory();
	TransientInstanceFactory(const TransientInstanceFactory &other);
	TransientInstanceFactory(TransientInstanceFactory &&other);
	virtual ~TransientInstanceFactory();

	TransientInstanceFactory &operator =(TransientInstanceFactory other);

	friend void swap(TransientInstanceFactory &left, TransientInstanceFactory &right);

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName);

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName);

	virtual void Remove(_In_ const std::string &interfaceTypeName);

private:
	std::map<std::string, std::shared_ptr<IInstantiator>> _instantiators;
};

void swap(TransientInstanceFactory &left, TransientInstanceFactory &right);
