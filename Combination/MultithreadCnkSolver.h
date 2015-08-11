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

		std::function<T (const T&, const T&)> calcFunction=
			[](const T& _n, const T& _k){
				if (_n < 0 || _k < 0)
					return static_cast<T>(0);

				return SimpleCnk<T>()(_n, _k); 
			};
		
		if (max_thread_count_ == 1){
			return calcFunction(n, k);
		}
		else{

			// Пока только на два потока.
			T result = 0;
			std::vector<std::future<T>> workers;

			workers.push_back(std::async(std::launch::async, calcFunction, n - 1, k));
			workers.push_back(std::async(std::launch::async, calcFunction, n - 1, k - 1));

			for (auto & w : workers){
				result += w.get();
			}
			return result;
		}
	}
};
