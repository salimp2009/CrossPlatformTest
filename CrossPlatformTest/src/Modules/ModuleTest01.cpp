//module;
//
//// include goes here
//#include <vector>
//#include <numeric>
//#include <algorithm>
//
//export module math;
//
//// import goes here
//
//export namespace math
//{
//
//	int add(int first, int second)
//	{
//
//
//		return first + second;
//
//	}
//
//	int getProduct(const std::vector<int>& vec)
//	{
//		return std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
//	}
//
//	int getSum(const std::vector<int>& vec)
//	{
//		int sum = 0;
//		std::for_each(vec.begin(), vec.end(), [&sum](auto& elem) {sum += elem * elem; });
//		return sum;
//	}
//
//
//
//}