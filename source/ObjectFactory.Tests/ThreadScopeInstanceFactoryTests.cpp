#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Registry.h>
#include <InstantiatorFactory.h>
#include <IInstanceFactory.h>
#include <ThreadScopeInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"
#include "TestThread.h"

class ThreadScopeInstanceFactoryTests : public testing::Test
{
protected:
	shared_ptr<IContainer> _container;
	shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp()
	{
		_container = make_shared<Container>();

		_instanceFactory = make_shared<ThreadScopeInstanceFactory>();
	};

	virtual void TearDown()
	{
		_container.reset();
		_instanceFactory.reset();
	};
};

TEST_F(ThreadScopeInstanceFactoryTests, GetInstance_CreationStrategyNotSet_ThrowsException)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}

TEST_F(ThreadScopeInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsSameInstanceOnSameThread)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());
	shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_EQ(one, two);
}

TEST_F(ThreadScopeInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsDifferentInstancesOnDifferentThreads)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	TestThread t(_container, _instanceFactory);

	t.Start();

	t.Stop();

	void *actual = t.GetReturnedInterfacePointer();

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one.get(), actual);
}

TEST_F(ThreadScopeInstanceFactoryTests, RemoveInstance_CreationStrategyNotSet_DoesNothing)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_NO_THROW(_instanceFactory->RemoveInstance(typeName.c_str()));
}

TEST_F(ThreadScopeInstanceFactoryTests, RemoveInstance_CreationStrategySet_RemovesInstance)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	_instanceFactory->RemoveInstance(typeName.c_str());

	shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName.c_str());
	shared_ptr<void> three = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, two);
	EXPECT_EQ(two, three);
}

TEST_F(ThreadScopeInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

	EXPECT_NE(one, __nullptr);

	_instanceFactory->Remove(typeName.c_str());

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName.c_str()), std::exception);
}
