#pragma
#include "RangesHeaders.hpp"

void Send(const std::span<char>& data)
{
	data[0] = 'z';
	for (const auto& text : data)
	{
		std::printf("%c ", text);
	}
	std::puts("");
}

