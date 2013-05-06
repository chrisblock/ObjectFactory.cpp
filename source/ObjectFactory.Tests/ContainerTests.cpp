#include "stdafx.h"

#include <Exception.h>
#include <IContainer.h>
#include <Container.h>
#include <Lifetimes.h>
#include <Registry.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class ContainerTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Transient);
	};
};

class ContainerTests : public testing::Test
{
protected:
	shared_ptr<IContainer> _container;

	virtual void SetUp()
	{
		_container = make_shared<Container>();

		_container->Initialize(_registry);
	};

	virtual void TearDown()
	{
		_container.reset();
	};

private:
	ContainerTestRegistry _registry;
};

TEST_F(ContainerTests, GetInstance_TypeNotRegistered_ThrowsException)
{
	EXPECT_THROW(_container->GetInstance<int>(), Exception*);
}

TEST_F(ContainerTests, GetInstance_RegisteredType_ReturnsInstance)
{
	shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, __nullptr);
}

TEST_F(ContainerTests, Inject_InstanceOfType_InjectedInstanceIsReturned)
{
	shared_ptr<TestImplementation> instance = make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	shared_ptr<ITestInterface> result1 = _container->GetInstance<ITestInterface>();
	shared_ptr<ITestInterface> result2 = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result1, instance);
	EXPECT_EQ(result2, instance);
	EXPECT_EQ(result1, result2);
}

TEST_F(ContainerTests, EjectAllInstancesOf_EjectedType_InjectedInstanceIsNotReturned)
{
	shared_ptr<TestImplementation> instance = make_shared<TestImplementation>();

	_container->Inject<ITestInterface>(instance);

	shared_ptr<ITestInterface> result = _container->GetInstance<ITestInterface>();

	EXPECT_EQ(result, instance);

	_container->EjectAllInstancesOf<ITestInterface>();

	result = _container->GetInstance<ITestInterface>();

	EXPECT_NE(result, instance);
}
