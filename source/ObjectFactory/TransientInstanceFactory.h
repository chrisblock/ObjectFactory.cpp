#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstanceFactory.h"

class TransientInstanceFactory : public IInstanceFactory
{
public:
	virtual ~TransientInstanceFactory();

	virtual void SetCreationStrategy(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &instantiator);

	virtual std::shared_ptr<void> GetInstance(const IContainer &container, LPCTSTR interfaceTypeName);

	virtual void Remove(LPCTSTR interfaceTypeName);

private:
	std::map<std::basic_string<TCHAR>, std::shared_ptr<IInstantiator>> _instantiators;
};
