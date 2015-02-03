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

	InstantiatorFactory &operator =(InstantiatorFactory other) = delete;

	template <typename T>
	static std::shared_ptr<IInstantiator> CreateInstantiator()
	{
		std::shared_ptr<IInstantiator> result = std::make_shared<VariadicArgumentInstantiator<T>>();

		return result;
	};

	template <typename T>
	static std::shared_ptr<IInstantiator> CreateInstantiator(const std::function<std::shared_ptr<void> (const IContainer &)> &lambda)
	{
		std::shared_ptr<IInstantiator> result = std::make_shared<LambdaInstantiator>(lambda);

		return result;
	};
};

#define DECLARE_INSTANTIATOR(TypeName) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>()

#define IMPLEMENT_INSTANTIATOR(TypeName, ...) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>() { std::shared_ptr<IInstantiator> result = std::make_shared<VariadicArgumentInstantiator<TypeName, ##__VA_ARGS__>>(); return result; }
