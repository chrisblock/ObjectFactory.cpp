#include "stdafx.h"

#include <LambdaInstantiator.h>

#include <Container.h>

class TypeWithPrimitiveDependency
{
public:
	TypeWithPrimitiveDependency(const std::int32_t timeout) :
		  _timeout(timeout)
	{
	};

	TypeWithPrimitiveDependency(const TypeWithPrimitiveDependency &other) = default;
	TypeWithPrimitiveDependency(TypeWithPrimitiveDependency &&other) = default;
	virtual ~TypeWithPrimitiveDependency() = default;

	TypeWithPrimitiveDependency &operator =(const TypeWithPrimitiveDependency &other) = default;
	TypeWithPrimitiveDependency &operator =(TypeWithPrimitiveDependency &&other) = default;

private:
	std::int32_t _timeout;
};

class Given_type_with_primitive_dependency : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

TEST_F(Given_type_with_primitive_dependency, When_getting_type_name_Then_type_is_returned)
{
	LambdaInstantiator<TypeWithPrimitiveDependency> instantiator([]() { return std::make_shared<TypeWithPrimitiveDependency>(42); });

	std::string expected = typeid (TypeWithPrimitiveDependency).name();

	EXPECT_EQ(expected, instantiator.GetType());
}

TEST_F(Given_type_with_primitive_dependency, When_getting_dependencies_Then_empty_list_is_returned)
{
	LambdaInstantiator<TypeWithPrimitiveDependency> instantiator([]() { return std::make_shared<TypeWithPrimitiveDependency>(42); });

	std::vector<std::string> actual = instantiator.GetDependencies();

	EXPECT_TRUE(actual.empty());
}

TEST_F(Given_type_with_primitive_dependency, When_instance_is_created_Then_instance_is_returned)
{
	Container container;

	LambdaInstantiator<TypeWithPrimitiveDependency> instantiator([]() { return std::make_shared<TypeWithPrimitiveDependency>(42); });

	std::shared_ptr<void> actual = instantiator.CreateInstance(container);

	EXPECT_NE(nullptr, actual);
}

TEST_F(Given_type_with_primitive_dependency, When_instance_is_created_Then_new_instance_is_returned_every_time)
{
	Container container;

	LambdaInstantiator<TypeWithPrimitiveDependency> instantiator([]() { return std::make_shared<TypeWithPrimitiveDependency>(42); });

	std::shared_ptr<void> one = instantiator.CreateInstance(container);
	std::shared_ptr<void> two = instantiator.CreateInstance(container);

	EXPECT_NE(one, two);
}
