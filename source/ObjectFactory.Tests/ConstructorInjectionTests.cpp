#include "stdafx.h"

#include <Container.h>
#include <IContainer.h>
#include <Registry.h>

#include "ITestInterface.h"
#include "TestImplementation.h"
#include "ConstructorInjectedImplementation.h"

class ConstructorInjectionTestRegistry : public Registry
{
public:
	virtual void Register(IContainer &container) const override
	{
		container.Register<ITestInterface, TestImplementation>(Lifetimes::Transient);
		container.Register<IConstructorInjectedInterface, ConstructorInjectedImplementation>(Lifetimes::Singleton);
	};
};

class ConstructorInjectionTests : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		_container = std::make_shared<Container>(_registry);
	};

	virtual void TearDown() override
	{
		_container.reset();
	};

	std::shared_ptr<IContainer> _container;

private:
	ConstructorInjectionTestRegistry _registry;
};

TEST_F(ConstructorInjectionTests, InterfaceRegistered_InstantiatorMacroUsedForConstructorInjection_ReturnsInstanceWithInjectedMemberInstance)
{
	std::shared_ptr<IConstructorInjectedInterface> one = _container->GetInstance<IConstructorInjectedInterface>();

	EXPECT_NE(nullptr, one);
	EXPECT_NE(nullptr, one->GetTestInterface());
}
