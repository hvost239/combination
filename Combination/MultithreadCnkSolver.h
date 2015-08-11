#pragma once

#include <future>
#include <functional>

#include "SimpleCnk.h"


/*
	Функциональный объект для расчета сочетания "C из n по k" в нескльких потоках.
	Для расчета используем формулу Cnk = n!/k!*(n-k)! и рукурентную формулу Cnk = Cn(k-1) + C(n-1)(k-1)
*/
template<class T>
class MultiThreadCnkSolver : std::binary_function < const T&, const T&, T > {
private:
	int max_thread_count_;
	
public:
	MultiThreadCnkSolver(int maxThreadCount){
		SetMaxThreadCount(maxThreadCount);
	}

	T operator()(const T& n, const T& k){
		if (n < 0 || k < 0 || k > n)
			throw std::invalid_argument("bad argument");

		return calc(n, k);
	}

	int MaxThreadCount()const {
		return max_thread_count_;
	}

	void SetMaxThreadCount(int value) {
		if (value < 1)
			throw std::invalid_argument("Count of thread can't be less then 1");

		max_thread_count_ = value;
	}

private:
	T calc(const T& n, const T& k){
		if (k == 0 || n == k)
			return 1;		
					
		int thread_count = (n > max_thread_count_) 
								? max_thread_count_
								: static_cast<int>(n);
			
		T result = 0;
		std::vector<std::pair<std::future<T>, int>> workers;

		SimpleCnk<int> coeffSolver;

		T tN = n - max_thread_count_ + 1;
		for (int i = 0; i < max_thread_count_; ++i){
			int coeff = coeffSolver(max_thread_count_ - 1, i);
			T tK = k - i;
			workers.push_back(
				std::make_pair(
					std::async(std::launch::async, SimpleCalc, tN, tK),
					coeff));
		}

		for (auto & w : workers){
			result += w.first.get() * w.second;
		}
		return result;
	}

	static T SimpleCalc(const T& n, const T& k) {
		if (n < 0 || k < 0)
			return static_cast<T>(0);

		return SimpleCnk<T>()(n, k);
	}
};
