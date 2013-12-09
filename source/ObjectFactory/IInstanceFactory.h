#pragma once

class IContainer;
class IInstantiator;

class IInstanceFactory
{
public:
	virtual ~IInstanceFactory();

	virtual void SetCreationStrategy(_In_z_ const char *interfaceTypeName, _In_ const std::shared_ptr<IInstantiator> &instantiator) = 0;

	virtual std::shared_ptr<void> GetInstance(_In_ const IContainer &container, _In_z_ const char *interfaceTypeName) = 0;

	virtual void RemoveInstance(_In_z_ const char *interfaceTypeName) = 0;

	virtual void Remove(_In_z_ const char *interfaceTypeName) = 0;
};
