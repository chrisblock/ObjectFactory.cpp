#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IInstanceFactory.h"

#include "Mutex.h"
#include "IInstantiator.h"
#include "IContainer.h"

class SingletonInstanceFactory : public IInstanceFactory
{
public:
	SingletonInstanceFactory();
	virtual ~SingletonInstanceFactory();

	virtual void SetCreationStrategy(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &instanceCreator);

	virtual shared_ptr<void> GetInstance(const IContainer &container, LPCTSTR interfaceTypeName);

	virtual void Remove(LPCTSTR interfaceTypeName);

	int GetNumberOfInstances() const;

private:
	Mutex _mutex;
	std::map<std::basic_string<TCHAR>, std::shared_ptr<void>> _instances;
	std::map<std::basic_string<TCHAR>, std::shared_ptr<IInstantiator>> _instanceCreators;
};
