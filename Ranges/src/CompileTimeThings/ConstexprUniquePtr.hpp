#include "RangesHeaders.hpp"

template<typename T>
class uniquePtr
{
public:
	constexpr uniquePtr(T* ptr) noexcept:data{ptr} {}
	constexpr ~uniquePtr() noexcept { delete data; }

	// TODO check if operator * should return *data
	constexpr T* operator->() const { return data; }
	constexpr T& operator*() const& { return *data; }

	constexpr auto operator<=>(const uniquePtr&) const = default;
	constexpr auto operator==(std::nullptr_t) const { return  data == nullptr; }


private:
	T* data;
};

