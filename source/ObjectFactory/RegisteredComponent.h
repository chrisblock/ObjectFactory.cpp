#pragma once

#include <string>

class RegisteredComponent
{
public:
	RegisteredComponent();
	RegisteredComponent(const std::string &registeredType, const std::string &resolvedType, const std::string &lifetime);
	RegisteredComponent(const RegisteredComponent &other);
	RegisteredComponent(RegisteredComponent &&other);
	~RegisteredComponent();

	RegisteredComponent &operator =(RegisteredComponent other);

	friend void swap(RegisteredComponent &left, RegisteredComponent &right);

	const std::string &GetRegisteredType() const;
	const std::string &GetResolvedType() const;
	const std::string &GetLifetime() const;

private:
	std::string _registeredType;
	std::string _resolvedType;
	std::string _lifetime;
};

void swap(RegisteredComponent &left, RegisteredComponent &right);

std::ostream &operator <<(std::ostream &stream, const RegisteredComponent &component);
std::wostream &operator <<(std::wostream &stream, const RegisteredComponent &component);
