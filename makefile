main: main.cpp
	g++ -o test main.cpp

metaprogramming: metaprogramming.cpp
	g++ -std=c++17 -o meta metaprogramming.cpp
