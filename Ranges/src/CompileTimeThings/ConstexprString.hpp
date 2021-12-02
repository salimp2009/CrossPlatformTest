#include "RangesHeaders.hpp"

#if defined (__GNUG__)   || defined(__clang__)
	# if not (__cpp_lib_constexpr_string > 201911)
	class string
	{
	
	
	
	
	
	};
	#else
		using std::string;
	#endif
#else
	using std::string;
#endif
