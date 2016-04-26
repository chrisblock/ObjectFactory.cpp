#include "stdafx.h"

#include <VariadicArgumentInstantiator.h>

#include <Container.h>

class TypeWithNoDependencies
{
public:
	TypeWithNoDependencies() = default;
	TypeWithNoDependencies(const TypeWithNoDependencies &other) = default;
	TypeWithNoDependencies(TypeWithNoDependencies &&other) = default;
	~TypeWithNoDependencies() = default;

	TypeWithNoDependencies &operator =(const TypeWithNoDependencies &other) = default;
	TypeWithNoDependencies &operator =(TypeWithNoDependencies &&other) = default;
};

class Given_type_with_no_dependencies : public ::testing::Test
{
protected:
	void SetUp() override
	{
	};

	void TearDown() override
	{
	};
};

TEST_F(Given_type_with_no_dependencies, When_getting_type_name_Then_type_is_returned)
{
	VariadicArgumentInstantiator<TypeWithNoDependencies> instantiator;

	std::string expected = typeid (TypeWithNoDependencies).name();

	EXPECT_EQ(expected, instantiator.GetType());
}

TEST_F(Given_type_with_no_dependencies, When_getting_dependencies_Then_empty_list_is_returned)
{
	VariadicArgumentInstantiator<TypeWithNoDependencies> instantiator;

	std::vector<std::string> actual = instantiator.GetDependencies();

	EXPECT_TRUE(actual.empty());
}

TEST_F(Given_type_with_no_dependencies, When_instance_is_created_Then_instance_is_returned)
{
	Container container;

	VariadicArgumentInstantiator<TypeWithNoDependencies> instantiator;

	std::shared_ptr<void> actual = instantiator.CreateInstance(container);

	EXPECT_NE(nullptr, actual);
}

TEST_F(Given_type_with_no_dependencies, When_instance_is_created_Then_new_instance_is_returned_every_time)
{
	Container container;

	VariadicArgumentInstantiator<TypeWithNoDependencies> instantiator;

	std::shared_ptr<void> one = instantiator.CreateInstance(container);
	std::shared_ptr<void> two = instantiator.CreateInstance(container);

	EXPECT_NE(one, two);
}
