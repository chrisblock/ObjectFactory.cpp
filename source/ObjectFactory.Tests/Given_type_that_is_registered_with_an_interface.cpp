#include "stdafx.h"

#include <Container.h>
#include <RegisteredComponent.h>
#include <Registry.h>

#include "ITestInterface.h"
#include "SimpleRegistry.h"
#include "TestImplementation.h"

class Given_type_that_is_registered_with_an_interface : public ::testing::Test
{
protected:
	std::shared_ptr<IContainer> _container;

	virtual void SetUp() override
	{
		_container = std::make_shared<Container>(_registry);
	};

	virtual void TearDown() override
	{
		_container.reset();
	};

private:
	SimpleRegistry<ITestInterface, TestImplementation> _registry;
};

TEST_F(Given_type_that_is_registered_with_an_interface, When_registered_components_are_requested_Then_one_is_returned)
{
	std::vector<RegisteredComponent> components = _container->GetRegisteredComponents();

	EXPECT_EQ(1, components.size());
}

TEST_F(Given_type_that_is_registered_with_an_interface, When_registered_components_are_requested_Then_ITestInterface_is_registered_type)
{
	std::vector<RegisteredComponent> components = _container->GetRegisteredComponents();

	RegisteredComponent first = components.front();

	std::string expected = typeid (ITestInterface).name();

	EXPECT_EQ(expected, first.GetRegisteredType());
}

TEST_F(Given_type_that_is_registered_with_an_interface, When_registered_components_are_requested_Then_TestImplementation_is_resolved_type)
{
	std::vector<RegisteredComponent> components = _container->GetRegisteredComponents();

	RegisteredComponent first = components.front();

	std::string expected = typeid (ITestInterface).name();

	EXPECT_EQ(expected, first.GetResolvedType());
}

TEST_F(Given_type_that_is_registered_with_an_interface, When_registered_type_is_requested_Then_instance_is_returned)
{
	std::shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, nullptr);
}

TEST_F(Given_type_that_is_registered_with_an_interface, When_instance_is_requested_Then_injected_instance_is_returned)
{
	std::shared_ptr<TestImplementation> instance = std::make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	std::shared_ptr<ITestInterface> result1 = _container->GetInstance<ITestInterface>();
	std::shared_ptr<ITestInterface> result2 = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result1, instance);
	EXPECT_EQ(result2, instance);
	EXPECT_EQ(result1, result2);
}

TEST_F(Given_type_that_is_registered_with_an_interface, When_instance_is_ejected_Then_injected_instance_is_not_returned)
{
	std::shared_ptr<TestImplementation> instance = std::make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	std::shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result, instance);

	_container->EjectAllInstancesOf<ITestInterface>();

	result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, instance);
}
