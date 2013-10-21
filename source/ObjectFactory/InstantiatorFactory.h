#pragma once

#include <memory>

#include "IInstantiator.h"
#include "DefaultConstructorInstantiator.h"
#include "VariadicArgumentInstantiator.h"

class InstantiatorFactory
{
public:
	template <class T>
	static std::shared_ptr<IInstantiator> CreateInstantiator()
	{
		std::shared_ptr<IInstantiator> result = make_shared<DefaultConstructorInstantiator<T>>();

		return result;
	};

private:
	InstantiatorFactory();
};

#define DECLARE_INSTANTIATOR(TypeName) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>()

#define IMPLEMENT_INSTANTIATOR(TypeName, ...) template <> std::shared_ptr<IInstantiator> InstantiatorFactory::CreateInstantiator<TypeName>() { std::shared_ptr<IInstantiator> result = make_shared<VariadicArgumentInstantiator<TypeName, ##__VA_ARGS__>>(); return result; }
