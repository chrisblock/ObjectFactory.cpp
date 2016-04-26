#pragma once

#include <functional>
#include <memory>

#include "IInstantiator.h"
#include "LambdaInstantiator.h"
#include "VariadicArgumentInstantiator.h"

class InstantiatorFactory
{
public:
	InstantiatorFactory() = delete;
	InstantiatorFactory(const InstantiatorFactory &other) = delete;
	InstantiatorFactory(InstantiatorFactory &&other) = delete;
	~InstantiatorFactory() = delete;

	InstantiatorFactory &operator =(InstantiatorFactory other) = delete;

	template <typename T>
	static std::shared_ptr<IInstantiator> CreateInstantiator()
	{
		std::shared_ptr<IInstantiator> result = std::make_shared<VariadicArgumentInstantiator<T>>();

		return result;
	};

private:
	template <typename TResult, typename... TArgs>
	static std::shared_ptr<IInstantiator> CreateLambdaInstantiator(const std::function<std::shared_ptr<TResult> (const std::shared_ptr<TArgs> &...)> &lambda)
	{
		return std::make_shared<LambdaInstantiator<TResult, TArgs...>>(lambda);
	};
};

#define DECLARE_INSTANTIATOR(TypeName) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>()

#define IMPLEMENT_INSTANTIATOR(TypeName, ...) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>() { std::shared_ptr<IInstantiator> result = std::make_shared<VariadicArgumentInstantiator<TypeName, ##__VA_ARGS__>>(); return result; }

#define IMPLEMENT_LAMBDA_INSTANTIATOR(TypeName, Lambda) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>() { auto fn = Lambda; std::shared_ptr<IInstantiator> result = CreateLambdaInstantiator(fn); return result; }
