#include "RangesHeaders.hpp"
#include <cstddef>
#include <cstdint>

#if defined (_MSC_VER)
	#include<Winsock.h>
#elif defined( __linux__ )
	#include <arpa/inet.h>



constexpr auto ReverseBytes(std::integral auto value)
{
	return[&]<std::size_t... I>(std::index_sequence<I...>)->decltype(value)
	{
		return ((((value >> I * 8) & 0xff) << ((8 * sizeof(value)) - (1 + I) * 8)) | ...);

	}(std::make_index_sequence<sizeof value>{});
}

template<std::integral T>
constexpr T ByteSwap(T value)
{
	if constexpr (std::endian::native == std::endian::big || (sizeof value == 1))
	{
		return value;
	}
	else
	{
		if (std::is_constant_evaluated())
		{
			return ReverseBytes(value);
		}
		else
		{
			if constexpr (std::same_as<T, std::uint64_t>)
			{
				// hton; means host to network in Unix/Linux kernel and POSIX standarts ;that converts bytes dependian platform specific endiannes
				// htonl does swap bytes for 32bits but we have 64 that is why we have shit the value 32bits 
				//then do first part of the swap using htonl then we do swaping on the full value so second half is swapped
				// and cast it to 64 bits and combine with the or (|) so we get the full 64 bit swapped value; need to confirm this 
				// C++23 will have std::byteswap which is constexpr https://en.cppreference.com/w/cpp/numeric/byteswap
				return htonl(value >> 32) | (static_cast<std::uint64_t>(htonl(value)) << 32);
			}
			else if constexpr (std::same_as<T, std::uint32_t>)
			{
				// swaps the 32 bit bytes runtime; more efficient since they use platform specific intrinsics
				return htonl(value);
			}
			else if constexpr (std::same_as<T, std::uint16_t>)
			{
				// 16bit swapping function
				return htons(value);
			}
		}
	}
}


static_assert(ByteSwap(std::uint64_t(0x123456789ABCDEF0)) == 0xF0DEBC9A78563412);
static_assert(ByteSwap(std::uint32_t(0x12345678)) == 0x78563412);
static_assert(ByteSwap(std::uint16_t(0x1234)) == 0x3412);
static_assert(ByteSwap(std::uint8_t(0x12)) == 0x12);
#endif
