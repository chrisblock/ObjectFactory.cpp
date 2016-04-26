#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IContainer.h"
#include "Lifetimes.h"

class IInstanceFactory;
class IInstantiator;
class RegisteredComponent;
class Registry;

class Container : public IContainer
{
public:
	Container();
	Container(_In_ const Registry &registry);
	Container(_In_ const Container &other);
	Container(_In_ Container &&other);
	virtual ~Container();

	Container &operator =(_In_ Container other);

	friend void swap(_Inout_ Container &left, _Inout_ Container &right);

	virtual void Initialize(_In_ const Registry &registry) override;

	virtual std::vector<RegisteredComponent> GetRegisteredComponents() const override;

protected:
	virtual void Register(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &implementationCreator, _In_ const Lifetimes::Lifetime lifetime) override;
	virtual void Remove(_In_ const std::string &interfaceTypeName);
	virtual std::shared_ptr<void> GetInstance(_In_ const std::string &interfaceTypeName) const override;
	virtual void Inject(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<void> &instance) override;
	virtual void EjectAllInstancesOf(_In_ const std::string &interfaceTypeName) override;

private:
	std::unordered_map<std::string, std::shared_ptr<void>> _injectedInstances;
	std::unordered_map<Lifetimes::Lifetime, std::shared_ptr<IInstanceFactory>> _factoriesByLifetime;
	std::unordered_map<std::string, std::shared_ptr<IInstanceFactory>> _factoriesByTypeName;
};

void swap(_Inout_ Container &left, _Inout_ Container &right);
