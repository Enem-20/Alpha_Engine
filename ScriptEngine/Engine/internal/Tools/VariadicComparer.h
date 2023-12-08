#pragma once

#ifndef VARIADIC_COMPARER
#define VARIADIC_COMPARER

#include<tuple>
#include<type_traits>

template <typename Sub, typename Super>
struct subset_of : std::false_type {};

template<typename Same, typename... AOther, typename... BOther>
struct subset_of<std::tuple<Same, AOther...>, std::tuple<Same, BOther...>>
	: subset_of<
	std::tuple<AOther...>
	, std::tuple<BOther...>
	> {};

template<typename ADifferent, typename BDifferent, typename... AOther, typename... BOther>
struct subset_of<std::tuple<ADifferent, AOther...>, std::tuple<BDifferent, BOther...>>
	: subset_of<
	std::tuple<ADifferent, AOther...>
	, std::tuple<BOther...>
	> {};

template<typename... B>
struct subset_of<std::tuple<>, std::tuple<B...>> : std::true_type {};

#endif