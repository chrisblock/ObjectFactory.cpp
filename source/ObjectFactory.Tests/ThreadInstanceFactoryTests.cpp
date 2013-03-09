#include "stdafx.h"

#include <IContainer.h>
#include <Exception.h>
#include <Registry.h>
#include <ObjectFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class ThreadTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Thread);
	};
};

class ThreadInstanceFactoryTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
		ThreadTestRegistry registry;

		ObjectFactory::Initialize(registry);
	};

	virtual void TearDown()
	{
		ObjectFactory::Clear();
	};
};

TEST_F(ThreadInstanceFactoryTests, TypeNotRegistered_ThrowsException)
{
	EXPECT_THROW(ObjectFactory::GetInstance<TestImplementation>(), Exception*);
}

TEST_F(ThreadInstanceFactoryTests, InterfaceRegisteredAsThreadScoped_ReturnsReferenceToSameInstanceOnSameThread)
{
	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();
	shared_ptr<ITestInterface> two = ObjectFactory::GetInstance<ITestInterface>();

	EXPECT_EQ(one.get(), two.get());
}

ULONG WINAPI ThreadMain(void *)
{
	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();

	return (ULONG) one.get();
}

TEST_F(ThreadInstanceFactoryTests, InterfaceRegisteredAsThreadScoped_GetInstanceCalledOnDifferentThreads_ReturnsReferenceToDifferentInstanceOnDifferentThreads)
{
	ULONG threadId = 0;
	ULONG flags = 0;

	HANDLE thread = ::CreateThread(__nullptr, 0, ThreadMain, __nullptr, flags, &threadId);

	::WaitForSingleObject(thread, INFINITE);

	ULONG result;

	::GetExitCodeThread(thread, &result);

	::CloseHandle(thread);

	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();

	EXPECT_NE((ULONG) one.get(), result);
}
