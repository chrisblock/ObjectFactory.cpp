#include "stdafx.h"

#include "LambdaInstantiator.h"

void swap(LambdaInstantiator &left, LambdaInstantiator &right)
{
	using std::swap;

	swap(left._lambda, right._lambda);
}

LambdaInstantiator::LambdaInstantiator(const std::function<std::shared_ptr<void> (const IContainer &)> &lambda) :
	  _lambda(lambda)
{
}

LambdaInstantiator::LambdaInstantiator(const LambdaInstantiator &other) :
	  _lambda(other._lambda)
{

}

LambdaInstantiator::LambdaInstantiator(LambdaInstantiator &&other)
{
	swap(*this, other);
}

LambdaInstantiator::~LambdaInstantiator()
{
}

LambdaInstantiator &LambdaInstantiator::operator =(LambdaInstantiator other)
{
	swap(*this, other);

	return *this;
}

std::shared_ptr<void> LambdaInstantiator::CreateInstance(_In_ const IContainer &container) const
{
	std::shared_ptr<void> result = _lambda(container);

	return result;
}
