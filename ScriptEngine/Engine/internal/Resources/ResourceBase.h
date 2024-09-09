#pragma once

#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include "API/ExportPropety.h"
#include "Tools/CompileTimeHash.h"

#include <string>
#include <memory>

template <size_t N>
constexpr inline size_t hash(size_t prime, const char(&str)[N], size_t Len = N - 1)
{
	return (Len <= 1) ? str[0] : (prime * hash(prime, str, Len - 1) + str[Len - 1]);
}

#define GETTYPE(ClassName) #ClassName;
#define GENERATETYPE(ClassName) inline static const std::string type = #ClassName;					\
								inline static constexpr size_t type_hash = COMPILE_TIME_CRC32_STR(#ClassName);			


//template<class Derived>
class DLLEXPORT ResourceBase {
public:
	ResourceBase() = delete;
	ResourceBase(const ResourceBase& resourceBase) = delete;
	ResourceBase(ResourceBase&& resourceBase) noexcept = delete;

	ResourceBase(std::string_view name/*, Derived* whatShouldBeStored*/);
	~ResourceBase();

	//std::shared_ptr<Derived> derived;
	std::string name;
};

#endif