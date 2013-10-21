#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <Registry.h>
#include <InstantiatorFactory.h>
#include <IInstanceFactory.h>
#include <ThreadScopeInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

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

typedef struct tagThreadArgument
{
	shared_ptr<IInstanceFactory> instanceFactory;
	shared_ptr<IContainer> container;
} ThreadArgument;

ULONG WINAPI ThreadMain(void *ptr)
{
	std::string typeName = typeid (ITestInterface).name();

	ThreadArgument *arg = static_cast<ThreadArgument *>(ptr);

	shared_ptr<void> result = arg->instanceFactory->GetInstance(*(arg->container), typeName.c_str());

	return (ULONG) result.get();
}

TEST_F(ThreadScopeInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsDifferentInstancesOnDifferentThreads)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName.c_str(), InstantiatorFactory::CreateInstantiator<TestImplementation>());

	ULONG threadId = 0;
	ULONG flags = 0;

	ThreadArgument arg = { _instanceFactory, _container };

	HANDLE thread = ::CreateThread(__nullptr, 0, ThreadMain, &arg, flags, &threadId);

	EXPECT_NE(thread, __nullptr);

	if (thread != __nullptr)
	{
		::WaitForSingleObject(thread, INFINITE);

		ULONG result;

		::GetExitCodeThread(thread, &result);

		::CloseHandle(thread);

		shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName.c_str());

		EXPECT_NE((ULONG) one.get(), result);
	}
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
