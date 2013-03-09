#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstantiator.h"

class IInstanceFactory
{
public:
	virtual ~IInstanceFactory();

	virtual void SetCreationStrategy(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &instanceCreator) = 0;

	virtual std::shared_ptr<void> GetInstance(const IContainer &container, LPCTSTR interfaceTypeName) = 0;

	virtual void Remove(LPCTSTR interfaceTypeName) = 0;
};
