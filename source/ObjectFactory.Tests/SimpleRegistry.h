#pragma once

#include <IContainer.h>
#include <Registry.h>

template <typename TInterface = void, typename TImplementation = void>
class SimpleRegistry : public Registry
{
public:
	SimpleRegistry() = default;
	SimpleRegistry(const SimpleRegistry &other) = default;
	SimpleRegistry(SimpleRegistry &&other) = default;
	virtual ~SimpleRegistry() = default;

	virtual void Register(_Inout_ IContainer &container) const override
	{
		container.Register<TInterface, TImplementation>();
	};
};

template <>
class SimpleRegistry<void, void> : public Registry
{
public:
	SimpleRegistry() = default;
	SimpleRegistry(const SimpleRegistry &other) = default;
	SimpleRegistry(SimpleRegistry &&other) = default;
	virtual ~SimpleRegistry() = default;

	virtual void Register(_Inout_ IContainer &container) const override
	{
		container;
	};
};

template <typename TConcreteClass>
class SimpleRegistry<TConcreteClass, void> : public Registry
{
public:
	SimpleRegistry() = default;
	SimpleRegistry(const SimpleRegistry &other) = default;
	SimpleRegistry(SimpleRegistry &&other) = default;
	virtual ~SimpleRegistry() = default;

	virtual void Register(_Inout_ IContainer &container) const override
	{
		container.Register<TConcreteClass>();
	};
};
