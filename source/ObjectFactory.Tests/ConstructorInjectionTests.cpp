#include "stdafx.h"

#include <IContainer.h>
#include <Registry.h>
#include <ObjectFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"
#include "ConstructorInjectedImplementation.h"

class ConstructorInjectionTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Transient);
		container.Register<IConstructorInjectedInterface, ConstructorInjectedImplementation>(Lifetimes::Singleton);
	};
};

class ConstructorInjectionTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
		ObjectFactory::Initialize(_registry);
	};

	virtual void TearDown()
	{
		ObjectFactory::Clear();
	};

private:
	ConstructorInjectionTestRegistry _registry;
};

TEST_F(ConstructorInjectionTests, InterfaceRegistered_InstantiatorMacroUsedForConstructorInjection_ReturnsInstanceWithInjectedMemberInstance)
{
	shared_ptr<IConstructorInjectedInterface> one = ObjectFactory::GetInstance<IConstructorInjectedInterface>();

	EXPECT_NE(__nullptr, one);
	EXPECT_NE(__nullptr, one->GetTestInterface());
}
