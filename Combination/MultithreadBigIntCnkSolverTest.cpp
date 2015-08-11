#include "stdafx.h"

#include <gtest\gtest.h>
#include "MultithreadCnkSolver.h"

#include <boost\multiprecision\cpp_int.hpp>


class MultithreadBinIntCnkSoverTest : public ::testing::TestWithParam < int > {

public:
	MultithreadBinIntCnkSoverTest()
			:solver(2){
	}

	void SetUp(){
		solver.SetMaxThreadCount(GetParam());
	}

	void TearDown(){
		solver.SetMaxThreadCount(2);
	}

protected:
	MultiThreadCnkSolver<boost::multiprecision::cpp_int> solver;
};


TEST_P(MultithreadBinIntCnkSoverTest, BigIntTest){
	
	std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> datas[] = {
		std::make_pair(1132, 834),
		std::make_pair(23247, 2543),
		std::make_pair(32343, 12367),
		std::make_pair(56735, 43763)
	};


	SimpleCnk<boost::multiprecision::cpp_int> simpleSolver;
	MultiThreadCnkSolver<boost::multiprecision::cpp_int> solver(4);

	for (auto& nk : datas){
		ASSERT_EQ(solver(nk.first, nk.second), simpleSolver(nk.first, nk.second));
	}
}

INSTANTIATE_TEST_CASE_P(AnyThreadCountTest, MultithreadBinIntCnkSoverTest, ::testing::Values(1, 2, 8, 256));

	
