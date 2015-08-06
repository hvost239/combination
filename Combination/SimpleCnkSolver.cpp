
#include "stdafx.h"

#include <gtest\gtest.h>
#include "SimpleCnk.h"

class SimpleCnkTest : public ::testing::Test{
protected:
	SimpleCnk<int> solver;
};


TEST_F(SimpleCnkTest, PascalTriangle){
	ASSERT_EQ(solver(0, 0), 1);
	ASSERT_EQ(solver(1, 0), 1);
	ASSERT_EQ(solver(1, 1), 1);

	ASSERT_EQ(solver(12, 8), 495);
	ASSERT_EQ(solver(14, 5), 2002);
}


TEST_F(SimpleCnkTest, NegativeValue){
	ASSERT_THROW(solver(-1, 2), std::invalid_argument);
	ASSERT_THROW(solver(1, -2), std::invalid_argument);
}

TEST_F(SimpleCnkTest, BadValue){
	ASSERT_THROW(solver(1, 2), std::invalid_argument);
}