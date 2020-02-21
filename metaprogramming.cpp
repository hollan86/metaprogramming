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
template<typename T>
struct dimof {
	static constexpr int value = 0;
};

template<typename T, int N>
struct dimof<T[N]> {
	static constexpr int value = 1 + dimof<T>::value;
};

//EXAMPLE 3:
template<typename T>
struct remove_const {
	using type = T;
};

template<typename T>
struct remove_const<const T> {
	using type = T;
};

int main() {
	//Example 1
	std::cout << t_abs<-5>::value << std::endl;
	//Example 2
	std::cout << dimof<int>::value << std::endl;
	std::cout << dimof<int[44]>::value << std::endl;
	std::cout << dimof<char[33][66]>::value << std::endl;
	std::cout << dimof<float[3][9][99]>::value << std::endl;
	//Example 3
	static_assert(std::is_same<remove_const<const int>::type,int>::value);
}
