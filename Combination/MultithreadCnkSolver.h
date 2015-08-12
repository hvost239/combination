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
	unsigned int max_thread_count_;
	
public:
	MultiThreadCnkSolver(unsigned int maxThreadCount){
		SetMaxThreadCount(maxThreadCount);
	}

	T operator()(const T& n, const T& k){
		if (n < 0 || k < 0 || k > n)
			throw std::invalid_argument("Bad argument. N and k must me more then 0, k <= n");

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
					
		unsigned int thread_count = (n > max_thread_count_) 
								? max_thread_count_
								: static_cast<unsigned int>(n);
			
		T result = 0;
		std::vector<std::pair<std::future<T>, unsigned int>> workers;

		SimpleCnk<unsigned int> coeffSolver;

		T tN = n - thread_count + 1;
		for (unsigned int i = 0; i < thread_count; ++i){
			unsigned int coeff = coeffSolver(thread_count - 1, i);
			T tK = k - i;
			// Возможна оптимизация: рассматривать ситуация когда tk может быть меньше 0 - уменьшать tn, добавась полезной нагрузки по максимальному количесту потоков
			
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
		if (n < 0 || k < 0 ||  k > n)
			return static_cast<T>(0);

		return SimpleCnk<T>()(n, k);
	}
};
