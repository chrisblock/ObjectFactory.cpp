#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Lifetimes.h>
#include <Registry.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class ContainerTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const override
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Transient);
	};
};

class ContainerTests : public testing::Test
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
	ContainerTestRegistry _registry;
};

TEST_F(ContainerTests, GetInstance_TypeNotRegistered_ThrowsException)
{
	EXPECT_THROW(_container->GetInstance<int>(), std::exception);
}

TEST_F(ContainerTests, GetInstance_RegisteredType_ReturnsInstance)
{
	std::shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, nullptr);
}

TEST_F(ContainerTests, Inject_InstanceOfType_InjectedInstanceIsReturned)
{
	std::shared_ptr<TestImplementation> instance = std::make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	std::shared_ptr<ITestInterface> result1 = _container->GetInstance<ITestInterface>();
	std::shared_ptr<ITestInterface> result2 = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result1, instance);
	EXPECT_EQ(result2, instance);
	EXPECT_EQ(result1, result2);
}

TEST_F(ContainerTests, EjectAllInstancesOf_EjectedType_InjectedInstanceIsNotReturned)
{
	std::shared_ptr<TestImplementation> instance = std::make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	std::shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result, instance);

	_container->EjectAllInstancesOf<ITestInterface>();

	result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, instance);
}
