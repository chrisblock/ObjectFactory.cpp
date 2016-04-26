#pragma once

#include <memory>
#include <string>

class IContainer;
class IInstantiator;
class RegisteredComponent;

class IInstanceFactory
{
public:
	virtual ~IInstanceFactory() = default;

	virtual void SetCreationStrategy(_In_ const std::string &interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator) = 0;

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_ const std::string &interfaceTypeName) = 0;

	virtual void RemoveInstance(_In_ const std::string &interfaceTypeName) = 0;

	virtual void Remove(_In_ const std::string &interfaceTypeName) = 0;

	virtual std::vector<RegisteredComponent> GetRegisteredComponents() const = 0;
};
