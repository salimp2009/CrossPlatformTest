#include "RangesHeaders.hpp"

#if defined (_MSC_VER)
	#include<Winsock.h>
#else
	#include <arpa/inet.h>
#endif

constexpr auto ReverseBytes(std::integral auto value)
{

	return[&]<std::size_t... I>(std::index_sequence<I...>)->decltype(value)
	{
		return ((((value >> I * 8) & 0xff) << ((8 * sizeof(value)) - (1 + I) * 8)) | ...);

	}(std::make_index_sequence<sizeof value>{});

}

