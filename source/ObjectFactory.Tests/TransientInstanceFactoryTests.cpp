#include "stdafx.h"

#include <IContainer.h>
#include <Registry.h>
#include <ObjectFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class TransientTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Transient);
	};
};

class TransientInstanceFactoryTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
		TransientTestRegistry registry;

		ObjectFactory::Initialize(registry);
	};

	virtual void TearDown()
	{
		ObjectFactory::Clear();
	};
};

TEST_F(TransientInstanceFactoryTests, Test)
{
	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();
	shared_ptr<ITestInterface> two = ObjectFactory::GetInstance<ITestInterface>();

	EXPECT_NE(one.get(), two.get());
}

TEST_F(TransientInstanceFactoryTests, InterfaceRegisteredAsTransient_ReturnsDifferentInstances)
{
	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();
	shared_ptr<ITestInterface> two = ObjectFactory::GetInstance<ITestInterface>();

	EXPECT_NE(one.get(), two.get());
}
