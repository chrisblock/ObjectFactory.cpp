#pragma once

#include <map>
#include <string>

#include "IContainer.h"
#include "Lifetimes.h"

class IInstanceFactory;
class IInstantiator;
class Registry;

class Container : public IContainer
{
public:
	Container();
	Container(const Container &other);
	virtual ~Container();

	Container &operator =(const Container &other);

	virtual void Initialize(_In_ const Registry &registry);

protected:
	virtual void Register(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime);
	virtual void Remove(_In_z_ const char *interfaceTypeName);
	virtual std::shared_ptr<void> GetInstance(_In_z_ const char *interfaceTypeName) const;
	virtual void Inject(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<void> &instance);
	virtual void EjectAllInstancesOf(_In_z_ const char *interfaceTypeName);

private:
	std::map<std::string, std::shared_ptr<void>> _injectedInstances;
	std::map<Lifetimes::Lifetime, std::shared_ptr<IInstanceFactory>> _factoriesByLifetime;
	std::map<std::string, std::shared_ptr<IInstanceFactory>> _factoriesByTypeName;
};
