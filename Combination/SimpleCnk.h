#pragma once
#include <functional>
#include <stdexcept>

template<class T>
class SimpleCnk : std::binary_function < const T&, const T&, T > {
private:

	/*
		begin * (begin - 1) * (begin - 2) * ... * end
	*/
	T MultRange(const T& begin, const T& end = 1){
		T result = 1;
		for (T it = begin; it >= end; --it){
			result *= it;
		}
		return result;
	}
	
public:
	T operator()(const T& n, const T& k){
		if (n < 0 || k < 0 || k > n)
			throw std::invalid_argument("bad argument");

		return k > n / 2
			? MultRange(n, k + 1) / MultRange(n - k)
			: MultRange(n, n - k + 1) / MultRange(k);
	}
};