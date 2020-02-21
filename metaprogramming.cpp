#include <iostream>
#include <climits>
#include <type_traits>

//EXAMPLE 1:
template <int N>
struct t_abs {
	static_assert(N != INT_MIN);
	static constexpr int value = (N < 0)? -N : N;
};

//EXAMPLE 2:
template<int VAL>
struct set_int {
	static constexpr int value = VAL;
};
template<typename T>
struct dimof : set_int<0> {};

template<typename T, int N>
struct dimof<T[N]> :set_int<1 + dimof<T>::value>{};

//EXAMPLE 3:
//added to refactor
template<typename T>
struct set_type {
	using type = T;
};
template<typename T>
struct remove_const : set_type<T>{};

template<typename T>
struct remove_const<const T> : set_type<T>{};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<typename T>
constexpr int dimof_v = dimof<T>::value;

int main() {
	//Example 1
	std::cout << t_abs<-5>::value << std::endl;
	//Example 2
	std::cout << dimof_v<int> << std::endl;
	std::cout << dimof_v<int[44]> << std::endl;
	std::cout << dimof_v<char[33][66]> << std::endl;
	std::cout << dimof_v<float[3][9][99]> << std::endl;
	//Example 3
	static_assert(std::is_same_v<remove_const_t<const int>,int>);
}
