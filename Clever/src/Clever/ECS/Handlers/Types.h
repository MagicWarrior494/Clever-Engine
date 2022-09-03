#pragma once
#include <bitset>
#include <cstdint>
namespace Clever {
	using EntityID = std::uint32_t;
	const EntityID MAX_SIGNATURES = 10000;
	using ComponentType = std::uint8_t;
	static const ComponentType MAX_COMPONENTS = 32;
	using Signature = std::bitset<MAX_COMPONENTS>;
}