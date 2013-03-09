#include "stdafx.h"

#include <IContainer.h>
#include <Exception.h>
#include <Registry.h>
#include <ObjectFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class SingletonTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Singleton);
	};
};

class SingletonInstanceFactoryTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
		SingletonTestRegistry registry;

		ObjectFactory::Initialize(registry);
	};

	virtual void TearDown()
	{
		ObjectFactory::Clear();
	};
};

TEST_F(SingletonInstanceFactoryTests, TypeNotRegistered_ThrowsException)
{
	EXPECT_THROW(ObjectFactory::GetInstance<TestImplementation>(), Exception*);
}

TEST_F(SingletonInstanceFactoryTests, InterfaceRegisteredAsSingleton_ReturnsReferenceToSameInstance)
{
	shared_ptr<ITestInterface> one = ObjectFactory::GetInstance<ITestInterface>();
	shared_ptr<ITestInterface> two = ObjectFactory::GetInstance<ITestInterface>();

	EXPECT_EQ(one.get(), two.get());
}
