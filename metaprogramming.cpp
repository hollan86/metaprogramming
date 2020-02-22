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


//EXAMPLE 4: CHECKING IF A TUPLE CONTAINS A CERTAIN TYPE

template <bool VAL>
struct set_bool {
	static constexpr bool value = VAL;
};

struct true_type : set_bool<true>{};
struct false_type : set_bool<false>{};

template <typename T, typename U>
struct is_same: false_type{};
template <typename T>
struct is_same<T,T>: true_type{};

template<typename T, typename U>
constexpr int is_same_v = is_same<T,U>::value;

//Now we can inspect the tuple
template<class Tuple, class T>
struct tuple_contains {
	static_assert(sizeof(Tuple) == -1,"tuple_contains called on non-tuple");
};

template<typename T>
struct tuple_contains<std::tuple<>,T> : false_type{};

template<class T, class Head, class... Rest>
struct tuple_contains<std::tuple<Head, Rest...>,T>:set_bool<is_same_v<Head,T> || tuple_contains<std::tuple<Rest...>,T>::value> {};

template<typename T, typename U>
constexpr int tuple_contains_v = tuple_contains<T,U>::value;
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
	//Example 4
	std::cout << tuple_contains_v<std::tuple<>,float> << std::endl;
	std::cout << tuple_contains_v<std::tuple<float,int,bool>,float> << std::endl;
	std::cout << tuple_contains_v<int,float> << std::endl;
}
