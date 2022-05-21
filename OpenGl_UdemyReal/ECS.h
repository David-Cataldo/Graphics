#pragma once

#include "pch.h"
#include <array>
#include <bitset>

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID GetUniqueComponentID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template<typename T>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetUniqueComponentID();
	return typeID;
}


constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;


