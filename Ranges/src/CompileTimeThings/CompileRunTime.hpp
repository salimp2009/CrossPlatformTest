#pragma once

void CompileTimevsRunTime();


consteval std::size_t StrLength(const char* str)
{

	return *str ? 1 + StrLength(str + 1) : 0;
	
}
