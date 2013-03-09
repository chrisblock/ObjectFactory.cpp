#pragma once

#include <tchar.h>
#include <string>
#include <map>

#include "IContainer.h"

#include "IInstanceFactory.h"

class Container : public IContainer
{
public:
	Container();
	virtual ~Container();

	void Initialize(const Registry &registry);

protected:
	virtual void Register(LPCTSTR interfaceTypeName, const std::shared_ptr<IInstantiator> &implementationCreator, const Lifetimes::Lifetime lifetime);
	virtual void Remove(LPCTSTR interfaceTypeName);
	virtual std::shared_ptr<void> GetInstance(LPCTSTR interfaceTypeName) const;

private:
	std::map<Lifetimes::Lifetime, std::shared_ptr<IInstanceFactory>> _factoriesByLifetime;
	std::map<std::basic_string<TCHAR>, std::shared_ptr<IInstanceFactory>> _factoriesByTypeName;
};
