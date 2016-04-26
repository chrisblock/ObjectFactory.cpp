#include "stdafx.h"

#include <InstantiatorFactory.h>

class Given_type_with_lambda_instantiator : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
	};

	virtual void TearDown() override
	{
	};
};

DECLARE_INSTANTIATOR(int);

template<>
std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<int>()
{
	std::function<std::shared_ptr<int>()> fn = []() {return std::make_shared<int>(42); };

	return CreateLambdaInstantiator(fn);
}

//IMPLEMENT_LAMBDA_INSTANTIATOR(int, []() { return std::make_shared<int>(42); });

TEST_F(Given_type_with_lambda_instantiator, Test)
{
	std::shared_ptr<IInstantiator> instantiator = InstantiatorFactory::CreateInstantiator<int>();
}
