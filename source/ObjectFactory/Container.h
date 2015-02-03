#pragma once

#include <map>
#include <memory>
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
	Container(Container &&other);
	virtual ~Container();

	Container &operator =(Container other);

	friend void swap(Container &left, Container &right);

	virtual void Initialize(_In_ const Registry &registry);

protected:
	virtual void Register(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime);
	virtual void Remove(_In_ const std::string &interfaceTypeName);
	virtual std::shared_ptr<void> GetInstance(_In_ const std::string &interfaceTypeName) const;
	virtual void Inject(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<void> &instance);
	virtual void EjectAllInstancesOf(_In_ const std::string &interfaceTypeName);

private:
	std::map<std::string, std::shared_ptr<void>> _injectedInstances;
	std::map<Lifetimes::Lifetime, std::shared_ptr<IInstanceFactory>> _factoriesByLifetime;
	std::map<std::string, std::shared_ptr<IInstanceFactory>> _factoriesByTypeName;
};

void swap(Container &left, Container &right);
