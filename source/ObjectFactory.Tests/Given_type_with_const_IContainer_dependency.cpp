#include "stdafx.h"

#include <Container.h>
#include <Registry.h>

#include "ClassWithConstContainerDependency.h"
#include "SimpleRegistry.h"

class Given_type_with_const_IContainer_dependency : public ::testing::Test
{
public:
	Given_type_with_const_IContainer_dependency() = default;
	virtual ~Given_type_with_const_IContainer_dependency() = default;

protected:
	SimpleRegistry<ClassWithConstContainerDependency> _registry;

	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(Given_type_with_const_IContainer_dependency, Should_get_same_container_injected)
{
	std::shared_ptr<IContainer> expected = std::make_shared<Container>(_registry);

	std::shared_ptr<ClassWithConstContainerDependency> obj = expected->GetInstance<ClassWithConstContainerDependency>();

	const std::shared_ptr<const IContainer> &actual = obj->GetContainer();

	EXPECT_EQ(expected, actual);
}

TEST_F(Given_type_with_const_IContainer_dependency, Should_get_container_used_to_create_object_injected)
{
	std::shared_ptr<IContainer> expected1 = std::make_shared<Container>(_registry);
	std::shared_ptr<IContainer> expected2 = std::make_shared<Container>(_registry);

	std::shared_ptr<ClassWithConstContainerDependency> obj1 = expected1->GetInstance<ClassWithConstContainerDependency>();
	std::shared_ptr<ClassWithConstContainerDependency> obj2 = expected2->GetInstance<ClassWithConstContainerDependency>();

	const std::shared_ptr<const IContainer> &actual1 = obj1->GetContainer();
	const std::shared_ptr<const IContainer> &actual2 = obj2->GetContainer();

	EXPECT_EQ(expected1, actual1);
	EXPECT_EQ(expected2, actual2);
	EXPECT_NE(expected1, actual2);
	EXPECT_NE(expected2, actual1);
}
