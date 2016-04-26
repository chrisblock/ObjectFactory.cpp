#include "stdafx.h"

#include <Container.h>
#include <RegisteredComponent.h>
#include <Registry.h>

#include "SimpleRegistry.h"

class Given_type_that_is_not_registered : public ::testing::Test
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
	SimpleRegistry<> _registry;
};

TEST_F(Given_type_that_is_not_registered, When_registered_components_are_requested_Then_empty_set_is_returned)
{
	std::vector<RegisteredComponent> components = _container->GetRegisteredComponents();

	EXPECT_EQ(0, components.size());
}

TEST_F(Given_type_that_is_not_registered, When_type_is_requested_Then_exception_is_thrown)
{
	EXPECT_THROW(_container->GetInstance<int>(), std::exception);
}
