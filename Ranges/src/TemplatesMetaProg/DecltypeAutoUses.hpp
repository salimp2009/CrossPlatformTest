#include "RangesHeaders.hpp"

//template<typename T>
//struct rose_tree;

// Not working right ????? Abort mission :)
template<typename T>
struct rose_tree :std::variant<T, std::vector<rose_tree<T>>>
{
	using std::variant<T, std::vector<rose_tree<T>>>::variant;
};

template<typename... Bases>
struct overloaded :Bases...
{
	using Bases::operator()...;
};

template<typename... Bases>
overloaded(Bases...)->overloaded<Bases...>;


static_assert(std::is_same_v<rose_tree<int>::variant , std::variant<int, std::vector<rose_tree<int>>> >);

// Not compiling ; and not understood the error 
//auto total_length(const rose_tree<std::string>& t)->int
//{
//	return std::visit(overloaded
//	{
//		[](const std::string& leaf)	->int { return  std::size(leaf) ; },
//		[&](auto& branch) ->int 
//		{
//			return std::transform_reduce(std::begin(branch), std::end(branch), 
//										0, std::plus{},
//										[](const auto& t) ->int { return total_length(t); });
//		} 
//		
//	}, t);
//}

