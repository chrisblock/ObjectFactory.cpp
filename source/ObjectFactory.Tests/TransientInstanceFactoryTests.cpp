#include "stdafx.h"

#include <IContainer.h>
#include <Container.h>
#include <IInstanceFactory.h>
#include <TransientInstanceFactory.h>

#include "ITestInterface.h"
#include "TestImplementation.h"

class TransientInstanceFactoryTests : public ::testing::Test
{
protected:
	std::shared_ptr<IContainer> _container;
	std::shared_ptr<IInstanceFactory> _instanceFactory;

	virtual void SetUp() override
	{
		_container = std::make_shared<Container>();

		_instanceFactory = std::make_shared<TransientInstanceFactory>();
	};

	virtual void TearDown() override
	{
		_container.reset();
		_instanceFactory.reset();
	};
};

TEST_F(TransientInstanceFactoryTests, GetInstance_CreationStrategyNotSet_ThrowsException)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName), std::exception);
}

TEST_F(TransientInstanceFactoryTests, GetInstance_CreationStrategySet_ReturnsDifferentInstances)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName, InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName);
	std::shared_ptr<void> two = _instanceFactory->GetInstance(*_container, typeName);

	EXPECT_NE(one, two);
}

TEST_F(TransientInstanceFactoryTests, RemoveInstance_CreationStrategyNotSet_DoesNothing)
{
	std::string typeName = typeid (ITestInterface).name();

	EXPECT_NO_THROW(_instanceFactory->RemoveInstance(typeName));
}

TEST_F(TransientInstanceFactoryTests, Remove_CreationStrategySet_RemovesTheCreationStrategyFromTheFactory)
{
	std::string typeName = typeid (ITestInterface).name();

	_instanceFactory->SetCreationStrategy(typeName, InstantiatorFactory::CreateInstantiator<TestImplementation>());

	std::shared_ptr<void> one = _instanceFactory->GetInstance(*_container, typeName);

	EXPECT_NE(one, nullptr);

	_instanceFactory->Remove(typeName);

	EXPECT_THROW(_instanceFactory->GetInstance(*_container, typeName), std::exception);
}
