#include "stdafx.h"

#include "RegisteredComponent.h"

#include <iomanip>

void swap(RegisteredComponent &left, RegisteredComponent &right)
{
	using std::swap;

	swap(left._lifetime, right._lifetime);
	swap(left._registeredType, right._registeredType);
	swap(left._resolvedType, right._resolvedType);
}

template <typename TChar>
std::basic_ostream<TChar> &__output(std::basic_ostream<TChar> &stream, const RegisteredComponent &component)
{
	const std::string &registered = component.GetRegisteredType();
	const std::string &resolved = component.GetResolvedType();
	const std::string &lifetime = component.GetLifetime();

	stream << std::setw(30) << registered.c_str()
		<< std::setw(30) << resolved.c_str()
		<< std::setw(30) << lifetime.c_str()
		<< std::endl;

	return stream;
}

std::ostream &operator <<(std::ostream &stream, const RegisteredComponent &component)
{
	return __output(stream, component);
}

std::wostream &operator <<(std::wostream &stream, const RegisteredComponent &component)
{
	return __output(stream, component);
}

RegisteredComponent::RegisteredComponent()
{
}

RegisteredComponent::RegisteredComponent(const std::string &registeredType, const std::string &resolvedType, const std::string &lifetime) :
	  _registeredType(registeredType)
	, _resolvedType(resolvedType)
	, _lifetime(lifetime)
{
}

RegisteredComponent::RegisteredComponent(const RegisteredComponent &other) :
	  _registeredType(other._registeredType)
	, _resolvedType(other._resolvedType)
	, _lifetime(other._lifetime)
{
}

RegisteredComponent::RegisteredComponent(RegisteredComponent &&other) :
	  RegisteredComponent()
{
	swap(*this, other);
}

RegisteredComponent::~RegisteredComponent()
{
}

RegisteredComponent &RegisteredComponent::operator =(RegisteredComponent other)
{
	swap(*this, other);

	return *this;
}

const std::string &RegisteredComponent::GetRegisteredType() const
{
	return _registeredType;
}

const std::string &RegisteredComponent::GetResolvedType() const
{
	return _resolvedType;
}

const std::string &RegisteredComponent::GetLifetime() const
{
	return _lifetime;
}
