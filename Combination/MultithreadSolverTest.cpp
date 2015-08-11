#include "stdafx.h"

#include <gtest\gtest.h>
#include "MultithreadCnkSolver.h"

#include <boost\multiprecision\cpp_int.hpp>

class MultithreadSolverTest : public ::testing::Test{
public:
	MultithreadSolverTest()
		:solver(2){
	}
protected:
	MultiThreadCnkSolver<long long> solver;
};


TEST_F(MultithreadSolverTest, PascalTriangle){
	ASSERT_EQ(solver(0, 0), 1);
	ASSERT_EQ(solver(1, 0), 1);
	ASSERT_EQ(solver(1, 1), 1);

	ASSERT_EQ(solver(12, 8), 495);
	ASSERT_EQ(solver(14, 5), 2002);
}


TEST_F(MultithreadSolverTest, NegativeValue){
	ASSERT_THROW(solver(-1, 2), std::invalid_argument);
	ASSERT_THROW(solver(1, -2), std::invalid_argument);
}

TEST_F(MultithreadSolverTest, BadValue){
	ASSERT_THROW(solver(1, 2), std::invalid_argument);
}

TEST_F(MultithreadSolverTest, NigatetaThreadCount){
	ASSERT_THROW(solver.SetMaxThreadCount(-1), std::invalid_argument);
}

TEST_F(MultithreadSolverTest, MaxThreadCount){
	int threadCount = 239;
	solver.SetMaxThreadCount(threadCount);
	ASSERT_EQ(solver.MaxThreadCount(), threadCount);
}

TEST_F(MultithreadSolverTest, SimpleTestEq){
	std::pair<long long, long long> datas[] = {
								 std::make_pair(11, 8), 
								 std::make_pair(27, 25),
								 std::make_pair(33, 12),
								 std::make_pair(35, 23)
								};


	SimpleCnk<long long> simpleSolver;
	for (auto& nk : datas){
		ASSERT_EQ(solver(nk.first, nk.second), simpleSolver(nk.first, nk.second));
	}
}


TEST(MultiThreadCnkSolverTest, BigInTest){

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